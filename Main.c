#include <stdio.h>
#include <stdlib.h>
#include "QuadraticSolution.h"
#include "Vector3D.h"
#include "LightPhysics.h"

int main(int argc, char* argc[]) {

    unsigned int width = 256;
    unsigned int height = 256;

    double** image_array = (double**) malloc(sizeof(double* * height));

    if (image_array == NULL) {
        printf("image_arrray null pointer error.\n");
        exit(1)
    }

    for (unsigned int i = 0; i < height; i++) {
        image_array[i] = (double*) malloc(sizeof(double * width));

        if (image_array[i] == NULL) {
            printf("image_array[%ui] null pointer error. Out of memory?\n", i);
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

            image_array[i][j] = 155;

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

            // TODO this must update for every object iff lesser t, keep that in mind
            if (t > 1) { //TODO is this correct?
                image_array[i][j] =



