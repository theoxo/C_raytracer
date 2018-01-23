/*
 * Vector3D source file
 * Theo Olausson
 * 23/01/18
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Vector3D {
    double x;
    double y;
    double z;
} Vector3D;

// Initiliaze values but do not allocate memory
void Vector3D_init(Vector3D* self, double x, double y, double z) {
    if (self == NULL) {
        printf("Vector3D_init: self is null.\n");
        return;
    }

    self->x = x;
    self->y = y;
    self->z = z;
}

// Initiliazation with allocation
Vector3D* Vector3D_create(double x, double y, double z) {
    Vector3D* vec = (Vector3D*) malloc(sizeof(Vector3D));

    if (vec == NULL) {
        printf("Vector3D_create: malloc failed; out of memory?\n");
        return NULL;
    }

    Vector3D_init(vec, x, y, z);
    return vec;
}

void Vector3D_destroy(Vector3D* self) {
    if (self != NULL) {
        free(self);
    }
}

double Vector3D_getX(Vector3D* self) {
    if (self != NULL) {
        return self->x;
    }

    printf("3DVector_getX: passed pointer is null.\n");
    return -1;
}

double Vector3D_getY(Vector3D* self) {
    if (self != NULL) {
        return self->y;
    }

    printf("3DVector_getY: passed pointer is null.\n");
    return -1;
}

double Vector3D_getZ(Vector3D* self) {
    if (self != NULL) {
        return self->z;
    }

    printf("3DVector_getZ: passed pointer is null.\n");
    return -1;
}

// Calculates dot product of vectors a and b
double Vector3D_dot(Vector3D* a, Vector3D* b) {
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
double Vector3D_magnitude(Vector3D* self) {
    return sqrt(Vector3D_dot(self, self));
}

// Calculates a-b
Vector3D* Vector3D_difference(Vector3D* a, Vector3D* b) {
    double x = Vector3D_getX(a) - Vector3D_getX(b);
    double y = Vector3D_getY(a) - Vector3D_getY(b);
    double z = Vector3D_getZ(a) - Vector3D_getZ(b);

    Vector3D* result = Vector3D_create(x, y, z);
    return result;
}

// Returns vec*factor
Vector3D* Vector3D_multiply(Vector3D* vec, double factor) {
    double x = Vector3D_getX(vec) * factor;
    double y = Vector3D_getY(vec) * factor;
    double z = Vector3D_getZ(vec) * factor;

    Vector3D* result = Vector3D_create(x, y, z);
    return result;
}

