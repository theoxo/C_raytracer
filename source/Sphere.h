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
Vector3D* Sphere_getCentre(Sphere* self);
double Sphere_getRadius(Sphere* self);
