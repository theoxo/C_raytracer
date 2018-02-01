#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif
#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif
#ifndef QUADRATICSOLUTION_H
#define QUADRATICSOLUTION_H
#include "QuadraticSolution.h"
#endif
#ifndef SPHERE_H
#define SPHERE_H
#include "Sphere.h"
#endif
#ifndef SPHERESNODE_H
#define SPHERESNODE_H
#include "SpheresNode.h"
#endif
#ifndef LIGHTPHYSICS_H
#define LIGHTPHYSICS_H
#include "LightPhysics.h"
#endif
#ifndef RGB_H
#define RGB_H
#include "RGB.h"
#endif
#ifndef PPM_H
#define PPM_H
#include "PPM.h"
#endif
#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "Vector3D.h"
#endif
#ifndef LIMITS_H
#define LIMITS_H
#include <limits.h>
#endif

int main(int argc, char* argv[]) {

    if (argc != 2) {
        printf("Usage: main.exe <name of file to write>\n");
        exit(1);
    }

    printf("\n\n========================\nWelcome. Beginning raytracing.\n\n\n");

    unsigned int width = 1024;
    unsigned int height = 1024;

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

    // Have now allocated the pixel array that is the image.
    // Let's fill it up.

    /*
     * INITILIAZE OBJECTS IN IMAGE
     */
    Vector3D* sphere1_centre = Vector3D_create(0.5, 0, 1);
    Sphere* sphere1 = Sphere_create(sphere1_centre, 0.5, 150, 0, 0);

    Vector3D* sphere2_centre = Vector3D_create(-1, 1, 3);
    Sphere* sphere2 = Sphere_create(sphere2_centre, 1, 0, 150, 0);
    SpheresNode* spheres_tail = SpheresNode_newList(sphere1);
    SpheresNode_add(sphere2);
    SpheresNode* spheres_traverser = spheres_tail;

    Vector3D* light_centre = Vector3D_create(-1, 1, 0); //free me TODO
    double light_luminance = 5;

    /*
     * Dimensions of image in space = 2x2, centered at the <0, 0, 1>
     */
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {

            image_array[i][j] =  RGB_create(0, 0, 0);
            if (image_array[i][j] == NULL) {
                printf("image_array[%u][%u] null pointer error. Out of memory?\n", i, j);
                exit(1);
            }

            double x_coordinate = -1 + 2* ( (double) j / (double) width );
            double y_coordinate = 1 - 2* ( (double) i / (double) height );
            
            // unit vector for the direction
            Vector3D* ray_direction = Vector3D_create(x_coordinate, y_coordinate, 1);
            //printf("Dir: %f\n", Vector3D_magnitude(ray_direction));
            // ^(recall image is parallel to the plane but centered at <0, 0, 1>)
            Vector3D* ray_origin = Vector3D_create(0, 0, 0);

            double t_min = 0;
            Sphere* sphere_to_draw;

            while (spheres_traverser != NULL) {

                QuadraticSolution* quadratic_solution = 
                    LightPhysics_ray_sphere_intersection(SpheresNode_getSphere(spheres_traverser), 
                            ray_origin, ray_direction);

                double t = fmin(QuadraticSolution_getPositive(quadratic_solution),
                            QuadraticSolution_getNegative(quadratic_solution)
                            );
                
                if (t <= 1) {
                   // try the other intersection
                    t = fmax(QuadraticSolution_getPositive(quadratic_solution),
                            QuadraticSolution_getNegative(quadratic_solution)
                            );
                }


                // update t_min if t current t is closer to the camera
                if ( (t > 1 && t < t_min) || t_min == 0 ) {
                    t_min = t;
                    sphere_to_draw = SpheresNode_getSphere(spheres_traverser);
                }

                spheres_traverser = SpheresNode_getNext(spheres_traverser);
                 
                // Free allocated memory
                QuadraticSolution_destroy(quadratic_solution);
            }

            if (t_min > 1) { //TODO is this correct?
                Vector3D* intersection_point = Vector3D_multiply(ray_direction, t_min);
                //printf("Ray_direction at: (%f, %f, %f)\n", Vector3D_getX(ray_direction), Vector3D_getY(ray_direction), Vector3D_getZ(ray_direction));
                //printf("Intersection at: (%f, %f, %f)\n", Vector3D_getX(intersection_point), Vector3D_getY(intersection_point), Vector3D_getZ(intersection_point));
                Vector3D* surface_normal = Vector3D_difference(intersection_point, Sphere_getCentre(sphere_to_draw));
                Vector3D* light_to_intersection = Vector3D_difference(intersection_point, light_centre);
                //printf("Surface_normal at: (%f, %f, %f)\n", Vector3D_getX(surface_normal), Vector3D_getY(surface_normal), Vector3D_getZ(surface_normal));
                //printf("light_to_intersection at: (%f, %f, %f)\n\n", Vector3D_getX(light_to_intersection), Vector3D_getY(light_to_intersection), Vector3D_getZ(light_to_intersection));

                // cos(Theta) = a.b / (|a|*|b|)
                //printf("Dot: %f\n", Vector3D_dot(surface_normal, light_to_intersection));
                //printf("Magnitude of surface normal: %f\n", Vector3D_magnitude(surface_normal));
                //printf("Magnitude of 'light to intersection': %f\n", Vector3D_magnitude(light_to_intersection));
                double cos = Vector3D_dot(surface_normal, light_to_intersection)
                                    / (Vector3D_magnitude(surface_normal) * Vector3D_magnitude(light_to_intersection));
                //printf("cos: %f\n\n", cos);
                cos = fmax(cos, 0);

                double energy = light_luminance * cos / pow(Vector3D_magnitude(light_to_intersection), 1);
                double red = Sphere_getRed(sphere_to_draw) * energy;
                if (red > 255) {red = 255;}
                double green = Sphere_getGreen(sphere_to_draw) * energy;
                if (green > 255) {green = 255;}
                double blue = Sphere_getBlue(sphere_to_draw) * energy;
                if (blue > 255) {blue = 255;}
                //printf("Energy: %f\n", energy);
                //printf("oldR: %u\n", Sphere_getRed(sphere_to_draw));
                //printf("oldG: %u\n", Sphere_getGreen(sphere_to_draw));
                //printf("oldB: %u\n", Sphere_getBlue(sphere_to_draw));
                // re-initialize in new colour(s)
                RGB_init(image_array[i][j], red, green, blue);
            }

            spheres_traverser = spheres_tail;

            // Free allocated memory
            Vector3D_destroy(ray_direction);
            Vector3D_destroy(ray_origin);
        }

    }

    //Destroy list  as it's now unused
    SpheresNode_destroyAllFollowing(spheres_tail);

    if (PPM_save(image_array, argv[1], height, width)) {
        printf("\nDone writing the file. Bye.\n========================\n\n");
    } else {
        printf("\nError writing file; see error trace.\n========================\n\n");
    }
    
    exit(0);
}
