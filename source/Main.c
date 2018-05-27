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

/*
 * DEFINITIONS
 */
#define WIDTH 1024
#define HEIGHT 1024
#define NUM_THREADS 4
/*
 * STRUCTS
 */
typedef struct thread_data_ {
    int thread_id;
    unsigned int heightStart, heightEnd;
    SpheresNode* spheres_tail;
    Vector3D light_centre;
    double light_luminance;
} thread_data;

/* 
 * GLOBAL AND CONSTANT VARIABLES
 */
//const unsigned int num_threads;
//const unsigned int width = 1024;
//const unsigned int height = 1024;
RGB image_array[HEIGHT][WIDTH];

/*
 * PROTOTYPES
 */
void * threadFillPixelArray(void * thread_data);
void localFillPixelArray(void * thread_data);
int save(char* file_name);


int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: main.exe <name of file to write>\n");
        exit(1);
    }

    //printf("\n\n========================\nWelcome. Beginning raytracing.\n\n\n");

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

    // Fill up the pixel array that is the image
    pthread_t threads[NUM_THREADS - 1];
    thread_data thread_data_array[NUM_THREADS];
    int rc;
    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        thread_data_array[i].thread_id = i;
        thread_data_array[i].heightStart = i*256;
        thread_data_array[i].heightEnd = (i+1)*256;
        thread_data_array[i].spheres_tail = spheres_tail;
        thread_data_array[i].light_centre = light_centre;
        thread_data_array[i].light_luminance = light_luminance;

        if (i != (NUM_THREADS - 1) ) { // Want to run last "thread" here in main
            rc = pthread_create(&threads[i], NULL, threadFillPixelArray, (void *) &thread_data_array[i]);
            if (rc) {
                printf("Error; thread return code is %d\n", rc);
                exit(1);
            }
       }
    }

    // Run 4th "thread"/segment locally
    threadFillPixelArray( (void *) &thread_data_array[NUM_THREADS-1]);

    /*
     * ---------------------------
     * magic silently happens in parallell
     * ---------------------------
     */

    void *status;
    for (unsigned int t = 0; t < 3; t++) {
        rc = pthread_join(threads[t], &status);
        if (rc) {
            printf("Error; thread return code from pthread_join is %d\n", rc);
            exit(-1);
        }
    }

    // Destroy list  as it's now unused
    //SpheresNode_destroyAllFollowing(spheres_tail);
    //Vector3D_destroy(light_centre);    
    
    if (save(argv[1])) {
        //printf("\nDone writing the file. Bye.\n========================\n\n");
    } else {
        printf("\nError writing file; see error trace.\n========================\n\n");
    }
    
    exit(0);
}

void *threadFillPixelArray(void *threadarg) {

    thread_data *mydata = (thread_data *) threadarg;
    int thread_id = mydata->thread_id;
    //printf("Thread %d started\n", thread_id);
    unsigned int heightStart = mydata->heightStart;
    unsigned int heightEnd = mydata->heightEnd;
    SpheresNode* spheres_tail = mydata->spheres_tail;
    Vector3D light_centre = mydata->light_centre;
    double light_luminance = mydata->light_luminance;

    SpheresNode* spheres_traverser = spheres_tail;
    /*
     * Dimensions of image in space = 2x2, centered at the <0, 0, 1>
     */
    for (unsigned int i = heightStart; i < heightEnd; i++) {
        for (unsigned int j = 0; j < WIDTH; j++) {

            // Initialize to pure black pixel
            image_array[i][j].red = 0;
            image_array[i][j].green = 0;
            image_array[i][j].blue = 0;

            double x_coordinate = -1 + 2* ( (double) j / (double) WIDTH );
            double y_coordinate = 1 - 2* ( (double) i / (double) HEIGHT );
            
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


                if (shadowed == 0) {
                    // Pixel is not shadowed, so update its colours accordingly

                    // cos(Theta) = a.b / (|a|*|b|)
                    double cos = Vector3D_dot(surface_normal, intersection_to_light)
                                        / (Vector3D_magnitude(surface_normal) 
                                                * Vector3D_magnitude(intersection_to_light));
                    cos = fmax(cos, 0);

                    double energy = light_luminance * cos 
                                        / pow(Vector3D_magnitude(intersection_to_light), 1.5);
                    double red = Sphere_getRed(sphere_to_draw) * energy;
                    if (red > 255) {red = 255;}
                    double green = Sphere_getGreen(sphere_to_draw) * energy;
                    if (green > 255) {green = 255;}
                    double blue = Sphere_getBlue(sphere_to_draw) * energy;
                    if (blue > 255) {blue = 255;}

                    // re-initialize in new colour(s)
                    image_array[i][j].red = red;
                    image_array[i][j].green = green;
                    image_array[i][j].blue = blue;

                }
            }

            spheres_traverser = spheres_tail;

            // Free allocated memory
            //Vector3D_destroy(ray_direction);
            //Vector3D_destroy(ray_origin);
        }
    }
    //printf("Thread %d finished.\n", thread_id);
    //pthread_exit(NULL); -- not needed if we join?
}

int save(char* file_name) {

    FILE* image = fopen(file_name, "w+");
    
    if (image == NULL) {
        printf("PPM_save: Failed to allocate file.\n");
        return 0;
    }

    fprintf(image, "P3\n%u %u\n255\n", WIDTH, HEIGHT);

    for (unsigned int i = 0; i < HEIGHT; i++) {
        for (unsigned int j = 0; j < WIDTH; j++) {
            fprintf(image, "%u %u %u ", image_array[i][j].red, 
                    image_array[i][j].green, image_array[i][j].blue);
             
        }
        fprintf(image, "\n");
    }

    // Done writing. Close
    fclose(image);

    return 1;
}
    
