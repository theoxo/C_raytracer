/*
 * Sphere header file
 * Theo Olausson
 * 27/01/18
 */

#ifndef VECTOR3D_H
#define VECTOR3D_H
#include "Vector3D.h"
#endif

typedef struct Sphere Sphere;
Sphere* Sphere_create(Vector3D* centre, double radius);
void Sphere_destroy(Sphere* self);
double Sphere_getCentre(Sphere* self);
double Sphere_getself(Sphere* self);
