/*
 * Vector3D source file
 * Theo Olausson
 * 23/01/18
 */

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

struct Vector3D {
    double x;
    double y;
    double z;
};

// Initiliaze values but do not allocate memory
void Vector3D_init(struct Vector3D* self, double x, double y, double z) {
    if (self == NULL) {
        printf("Vector3D_init: self is null.\n");
        return;
    }

    self->x = x;
    self->y = y;
    self->z = z;
}

// Initiliazation with allocation
struct Vector3D* Vector3D_create(double x, double y, double z) {
    struct Vector3D* vec = (struct Vector3D*) malloc(sizeof(struct Vector3D));

    if (vec == NULL) {
        printf("Vector3D_create: malloc failed; out of memory?\n");
        return NULL;
    }

    Vector3D_init(vec, x, y, z);
    return vec;
}

void Vector3D_destroy(struct Vector3D* self) {
    if (self != NULL) {
        free(self);
    }
}

double Vector3D_getX(struct Vector3D* self) {
    if (self != NULL) {
        return self->x;
    }

    printf("3DVector_getX: passed pointer is null.\n");
    return -1;
}

double Vector3D_getY(struct Vector3D* self) {
    if (self != NULL) {
        return self->y;
    }

    printf("3DVector_getY: passed pointer is null.\n");
    return -1;
}

double Vector3D_getZ(struct Vector3D* self) {
    if (self != NULL) {
        return self->z;
    }

    printf("3DVector_getZ: passed pointer is null.\n");
    return -1;
}

// Calculates dot product of vectors a and b
double Vector3D_dot(struct Vector3D* a, struct Vector3D* b) {
    if (a == NULL || b == NULL) {
        printf("Vector3D_dot:  null reference to parameter.\n");
        return -1;
    }

    double dot_product = ( Vector3D_getX(a) * Vector3D_getX(b) )
                        + ( Vector3D_getY(a) * Vector3D_getY(b) )
                        + ( Vector3D_getZ(a) * Vector3D_getZ(b) );

    return dot_product;
}

// Calculates the magnitude of the given vector
double Vector3D_magnitude(struct Vector3D* self) {
    return sqrt(Vector3D_dot(self, self));
}

// Calculates a-b
struct Vector3D* Vector3D_difference(struct Vector3D* a, struct Vector3D* b) {
    double x = Vector3D_getX(a) - Vector3D_getX(b);
    double y = Vector3D_getY(a) - Vector3D_getY(b);
    double z = Vector3D_getZ(a) - Vector3D_getZ(b);

    struct Vector3D* result = Vector3D_create(x, y, z);
    return result;
}

// Returns vec*factor
struct Vector3D* Vector3D_multiply(struct Vector3D* vec, double factor) {
    double x = Vector3D_getX(vec) * factor;
    double y = Vector3D_getY(vec) * factor;
    double z = Vector3D_getZ(vec) * factor;

    struct Vector3D* result = Vector3D_create(x, y, z);
    return result;
}

