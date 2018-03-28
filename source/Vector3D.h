/*
 * 3D-Vector header file
 * Theo Olausson
 * 23/01/18
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "Vector3D.h"
typedef struct Vector3D {
    double x, y, z;
} Vector3D;
void Vector3D_init(Vector3D* self, double x, double y, double z);
Vector3D* Vector3D_create(double x, double y, double z);
void Vector3D_destroy(Vector3D* self);
double Vector3D_getX(const Vector3D* self);
double Vector3D_getY(const Vector3D* self);
double Vector3D_getZ(const Vector3D* self);
Vector3D* Vector3D_copy(const Vector3D* source);
double Vector3D_dot(const Vector3D* a, const Vector3D* b);
double Vector3D_magnitude(const Vector3D* self);
Vector3D* Vector3D_difference(const Vector3D* a, const Vector3D* b);
Vector3D* Vector3D_multiply(const Vector3D* vec, double factor);
#endif
