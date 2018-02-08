#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "QuadraticSolution.h"
#include "Sphere.h"
#include "SpheresNode.h"
#include "LightPhysics.h"
#include "RGB.h"
#include "PPM.h"
#include "Vector3D.h"
#include <pthread.h>

typedef struct thread_data_ {
    int thread_id;
    unsigned int heightStart, heightEnd, width;
    RGB*** pixel_array;
    SpheresNode* spheres_tail;
    Vector3D light_centre;
    double light_luminance;
} thread_data;

void * fillPixelArray(void * thread_data);

int main(int argc, char* argv[]) {

    unsigned int height = 1024;
    unsigned int width = 1024;

    if (argc != 2) {
        printf("Usage: main.exe <name of file to write>\n");
        exit(1);
    }

    printf("\n\n========================\nWelcome. Beginning raytracing.\n\n\n");

    // Note 2D-array, third pointer is to actual RGB itself
    RGB*** image_array = (RGB***) malloc(sizeof(RGB**) * height);

    if (image_array == NULL) {
        printf("image_arrray null pointer error.\n");
        exit(1);
    }

    for (unsigned int i = 0; i < height; i++) {
        image_array[i] = (RGB**) malloc(sizeof(RGB*) * width);

        if (image_array[i] == NULL) {
            printf("image_array[%u] null pointer error. Out of memory?\n", i);
            exit(1);
        }
    }

    /*
     * INITILIAZE OBJECTS IN IMAGE
     */
    Vector3D sphere1_centre;
    Vector3D_init(&sphere1_centre, 1, 2, 2);
    Sphere* sphere1 = Sphere_create(&sphere1_centre, 0.5, 150, 0, 0);

    Vector3D sphere2_centre;
    Vector3D_init(&sphere2_centre, -1, 1, 3);
    Sphere* sphere2 = Sphere_create(&sphere2_centre, 1, 0, 150, 0);
    SpheresNode* spheres_tail = SpheresNode_newList(sphere1);
    SpheresNode_add(sphere2);

    Vector3D sphere3_centre; 
    Vector3D_init(&sphere3_centre, 0, 0, 10);
    Sphere* sphere3 = Sphere_create(&sphere3_centre, 6, 0, 0, 150);
    SpheresNode_add(sphere3);

    Vector3D light_centre;
    Vector3D_init(&light_centre, -1, 1, 0);
    double light_luminance = 5;

    // Have now allocated the pixel array that is the image.
    // Let's fill it up.
    pthread_t threads[4];
    thread_data thread_data_array[4];
    int rc;
    for (unsigned int i = 0; i < 4; i++) {
        thread_data_array[i].thread_id = i;
        thread_data_array[i].heightStart = i*256;
        thread_data_array[i].heightEnd = (i+1)*256;
        thread_data_array[i].width = width;
        thread_data_array[i].pixel_array = image_array;
        thread_data_array[i].spheres_tail = spheres_tail;
        thread_data_array[i].light_centre = light_centre;
        thread_data_array[i].light_luminance = light_luminance;

        rc = pthread_create(&threads[i], NULL, fillPixelArray, (void *) &(thread_data_array[i]));
        if (rc) {
            printf("Error; thread return code is %d\n", rc);
            exit(1);
        }
    }

    /*
     * ---------------------------
     * magic silently happens in parallell
     * ---------------------------
     */
    void *status;
    for (unsigned int t = 0; t < 2; t++) {
        rc = pthread_join(threads[t], &status);
        if (rc) {
            printf("Error; thread return code from pthread_join is %d\n", rc);
            exit(-1);
        }
    }

    // Destroy list  as it's now unused
    //SpheresNode_destroyAllFollowing(spheres_tail);
    //Vector3D_destroy(light_centre);    
    
    if (PPM_save(image_array, argv[1], height, width)) {
        printf("\nDone writing the file. Bye.\n========================\n\n");
    } else {
        printf("\nError writing file; see error trace.\n========================\n\n");
    }
    
    pthread_exit(NULL);
}

void *fillPixelArray(void *threadarg) {

    thread_data *mydata = (thread_data *) threadarg;
    unsigned int heightStart = mydata->heightStart;
    unsigned int heightEnd = mydata->heightEnd;
    unsigned int width = mydata->width;
    RGB*** image_array = mydata->pixel_array;
    SpheresNode* spheres_tail = mydata->spheres_tail;
    Vector3D light_centre = mydata->light_centre;
    double light_luminance = mydata->light_luminance;

    SpheresNode* spheres_traverser = spheres_tail;
    /*
     * Dimensions of image in space = 2x2, centered at the <0, 0, 1>
     */
    for (unsigned int i = heightStart; i < heightEnd; i++) {
        for (unsigned int j = 0; j < width; j++) {

            image_array[i][j] =  RGB_create(0, 0, 0);
            if (image_array[i][j] == NULL) {
                printf("image_array[%u][%u] null pointer error. Out of memory?\n", i, j);
                exit(1);
            }

            double x_coordinate = -1 + 2* ( (double) j / (double) width );
            double y_coordinate = 1 - 2* ( (double) i / (double) (1024) ); //fixme TODO shouldn't be hardcoded lol
            
            // unit vector for the direction
            Vector3D ray_direction = {x_coordinate, y_coordinate, 1};
            // ^(recall image is parallel to the plane but centered at <0, 0, 1>)
            
            Vector3D ray_origin = {0, 0, 0};

            double t_min = 0;
            Sphere* sphere_to_draw;

            while (spheres_traverser != NULL) {

                QuadraticSolution* quadratic_solution = 
                    LightPhysics_ray_sphere_intersection(SpheresNode_getSphere(spheres_traverser), 
                            &ray_origin, &ray_direction);

                double t = fmin(QuadraticSolution_getPositive(quadratic_solution),
                            QuadraticSolution_getNegative(quadratic_solution)
                            );
                
                if (t <= 1) {
                   // try the other intersection
                    t = fmax(QuadraticSolution_getPositive(quadratic_solution),
                            QuadraticSolution_getNegative(quadratic_solution)
                            );
                }


                // update t_min if current t is closer to the camera (/origin)
                if ( (t > 1 && t < t_min) || t_min == 0 ) {
                    t_min = t;
                    sphere_to_draw = SpheresNode_getSphere(spheres_traverser);
                }

                spheres_traverser = SpheresNode_getNext(spheres_traverser);
                 
                // Free allocated memory
                //QuadraticSolution_destroy(quadratic_solution);
            }

            if (t_min > 1) { 
                Vector3D* intersection_point = Vector3D_multiply(&ray_direction, t_min);
                Vector3D* surface_normal = Vector3D_difference(intersection_point, 
                                            Sphere_getCentre(sphere_to_draw));
                Vector3D* intersection_to_light = Vector3D_difference(&light_centre, intersection_point);

                spheres_traverser = spheres_tail;
                
                unsigned int shadowed = 0;

                while (spheres_traverser != NULL) {
                    Sphere* sphere = SpheresNode_getSphere(spheres_traverser);

                    if (sphere != sphere_to_draw) {
                        // check if lies between light and intersection
                        QuadraticSolution* quadratic_solution = 
                            LightPhysics_ray_sphere_intersection(
                                    sphere, intersection_point, intersection_to_light
                                    );

                        if (fmax(QuadraticSolution_getPositive(quadratic_solution),
                                QuadraticSolution_getNegative(quadratic_solution)
                              ) > 0) {
                            shadowed = 1;
                        }

                        //QuadraticSolution_destroy(quadratic_solution);

                        if (shadowed == 1) {
                            break;
                        }
                    }

                    spheres_traverser = SpheresNode_getNext(spheres_traverser);
                }

                double red = 0;
                double green = 0;
                double blue = 0;

                if (shadowed == 0) {
                    // cos(Theta) = a.b / (|a|*|b|)
                    double cos = Vector3D_dot(surface_normal, intersection_to_light)
                                        / (Vector3D_magnitude(surface_normal) 
                                                * Vector3D_magnitude(intersection_to_light));
                    cos = fmax(cos, 0);

                    double energy = light_luminance * cos 
                                        / pow(Vector3D_magnitude(intersection_to_light), 1.5);
                    red = Sphere_getRed(sphere_to_draw) * energy;
                    if (red > 255) {red = 255;}
                    green = Sphere_getGreen(sphere_to_draw) * energy;
                    if (green > 255) {green = 255;}
                    blue = Sphere_getBlue(sphere_to_draw) * energy;
                    if (blue > 255) {blue = 255;}

                    // re-initialize in new colour(s)
                    RGB_init(image_array[i][j], red, green, blue);

                }
            }

            spheres_traverser = spheres_tail;

            // Free allocated memory
            //Vector3D_destroy(ray_direction);
            //Vector3D_destroy(ray_origin);
        }
    }
    pthread_exit(NULL);
}
