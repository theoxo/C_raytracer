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
Sphere* Sphere_create(Vector3D* centre, double radius, unsigned int red, unsigned int green, 
        unsigned int blue);
void Sphere_destroy(Sphere* self);
Vector3D* Sphere_getCentre(Sphere* self);
double Sphere_getRadius(Sphere* self);
unsigned int Sphere_getRed(Sphere* self);
unsigned int Sphere_getGreen(Sphere* self);
unsigned int Sphere_getBlue(Sphere* self);
void Sphere_scaleColors(struct Sphere* self, double factor); 
