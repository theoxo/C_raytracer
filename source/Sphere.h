/*
 * Sphere header file
 * Theo Olausson
 * 27/01/18
 */

#include "Vector3D.h"

typedef struct Sphere Sphere;
Sphere* Sphere_create(Vector3D* centre, radius self);
void Sphere_destroy(Sphere* self);
double Sphere_getCentre(Sphere* self);
double Sphere_getself(Sphere* self);
