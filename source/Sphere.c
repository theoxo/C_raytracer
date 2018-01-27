/*
 * Sphere source file
 * Theo Olausson
 * 27/01/18
 */

#include <stdio.h>
#include <stdlib.h>
#include "Vector3D.h"

struct Sphere {
    double radius;
    Vector3D* centre;
};

// Initiliaze values but do not allocate memory
void Sphere_init(struct Sphere* self, Vector3D* centre, double radius) {
    if (self == NULL) {
        printf("Sphere_init: self is null.\n");
        return;
    }

    self->centre = centre;
    self->radius = radius;
}

// Initiliazation with allocation
struct Sphere* Sphere_create(Vector3D* centre, double radius) {
    struct Sphere* sphere = (struct Sphere*) malloc(sizeof(struct Sphere));

    if (sphere == NULL) {
        printf("Sphere_create: malloc failed; out of memory?\n");
        return NULL;
    }

    Sphere_init(sphere, centre, radius);
    return sphere;
}

void Sphere_destroy(struct Sphere* self) {
    if (self != NULL) {
        free(self);
    }
}

Vector3D* Sphere_getCentre(struct Sphere* self) {
    if (self != NULL) {
        return self->centre;
    }

    printf("3DVector_getCentre: passed pointer is null.\n");
    return NULL;
}

double Sphere_getRadius(struct Sphere* self) {
    if (self != NULL) {
        return self->radius;
    }

    printf("3DVector_getRadius: passed pointer is null.\n");
    return -1;
}
