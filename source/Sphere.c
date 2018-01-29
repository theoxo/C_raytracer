/*
 * Sphere source file
 * Theo Olausson
 * 27/01/18
 */

#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif
#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif
#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "Vector3D.h"
#endif

struct Sphere {
    double radius;
    Vector3D* centre;
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

// Initiliaze values but do not allocate memory
void Sphere_init(struct Sphere* self, Vector3D* centre, double radius, unsigned int red,
        unsigned int green, unsigned int blue) {

    if (self == NULL) {
        printf("Sphere_init: self is null.\n");
        return;
    }

    self->centre = centre;
    self->radius = radius;
    self->red = red % 256;
    self->green = green % 256;
    self->blue = blue % 256;
}

// Initiliazation with allocation
struct Sphere* Sphere_create(Vector3D* centre, double radius, unsigned int red, unsigned int green,
        unsigned int blue) {

    struct Sphere* sphere = (struct Sphere*) malloc(sizeof(struct Sphere));

    if (sphere == NULL) {
        printf("Sphere_create: malloc failed; out of memory?\n");
        return NULL;
    }

    Sphere_init(sphere, centre, radius, red, green, blue);
    return sphere;
}

void Sphere_destroy(struct Sphere* self) {
    if (self != NULL) {
        free(self->centre);
        free(self);
    }
}

Vector3D* Sphere_getCentre(struct Sphere* self) {
    if (self != NULL) {
        return self->centre;
    }

    printf("Sphere_getCentre: passed pointer is null.\n");
    return NULL;
}

double Sphere_getRadius(struct Sphere* self) {
    if (self != NULL) {
        return self->radius;
    }

    printf("Sphere_getRadius: passed pointer is null.\n");
    return -1;
}

unsigned int Sphere_getRed(struct Sphere* self) {
    if (self != NULL) {
        return self->red;
    }

    printf("Sphere_getRed: passed pointer is null.\n");
}

unsigned int Sphere_getGreen(struct Sphere* self) {
    if (self != NULL) {
        return self->green;
    }

    printf("Sphere_getGreen: passed pointer is null.\n");
}

unsigned int Sphere_getBlue(struct Sphere* self) {
    if (self != NULL) {
        return self->blue;
    }

    printf("Sphere_getBlue: passed pointer is null.\n");
}
