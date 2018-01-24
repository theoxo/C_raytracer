#include <stdio.h>
#include <stdlib.h>
#include "QuadraticSolution.h"
#include "Vector3D.h"
#include "LightPhysics.h"
#include "RGB.h"
#include "PPM.h"

int main(int argc, char* argv[]) {

    if (argc != 1) {
        printf("Usage: ./a.out <file_name>\n");
        exit(1);
    }

    unsigned int width = 256;
    unsigned int height = 256;

    // Note 2D-array, third pointer is to actual RGB itself
    RGB*** image_array = (RGB***) malloc(sizeof(RGB**) * height);

    if (image_array == NULL) {
        printf("image_arrray null pointer error.\n");
        exit(1)
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
     * Dimensions of image in space = 2x2, centered at the <0, 0, 1>
     */
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {

            image_array[i][j] =  RGB_create(155, 155, 155);
            if (image_array[i][j] == NULL) {
                printf("image_array[%u][%u] null pointer error. Out of memory?\n", i, j);
                exit(1);
            }

            double x_coordinate = -1 + ( (double) j / (double) width );
            double y_coordinate = -1 + ( (double) i / (double) height );
            
            Vector3D* ray_direction = Vector3D_create(x_coordinate, y_coordinate, 1);
            // ^(recall image is parallel to the plane but centered at <0, 0, 1>)
            Vector3D* ray_origin = Vector3D_create(0, 0, 0);

            // NOTE THIS IS TEMPORARY, TODO LOOP OVER ALL OBJECTS
            Vector3D* sphere_centre = Vector3D_create(0, 0, 3);
            double sphere_radius = 1;

            QuadraticSolution* quadratic_solution = 
                LightPhysics_ray_sphere_intersection(sphere_centre, sphere_radius, 
                        ray_origin, ray_direction);

            double t = fmin(QuadraticSolution_getPositive(quadratic_solution),
                        QuadraticSolution_getNegative(quadratic_solution)
                        );
            
            // Free allocated memory
            QuadraticSolution_destroy(quadratic_solution);
            Vector3D_destroy(ray_direction);
            Vector3D_destroy(ray_origin);
            Vector3D_destroy(sphere_centre);

            // TODO this must update for every object iff lesser t, keep that in mind
            if (t > 1) { //TODO is this correct?
                // re-initialize in new colour(s)
                RGB_init(image_array[i][j], 200, 0, 0);
            }
        }
    }

    if (PPM_save(image_array, file_name, height, width)) {
        printf("\n\n-------------------\nDone writing the file. Bye.\n");
    } else {
        printf("\n\n-------------------\nError writing file; see error trace.");
    }
    
    exit(0);
}



