/*
 * Sphere header file
 * Theo Olausson
 * 27/01/18
 */

#ifndef SPHERE_H
#define SPHERE_H
#include "Vector3D.h"
typedef struct Sphere Sphere;
Sphere* Sphere_create(Vector3D* centre, double radius, unsigned int red, unsigned int green, 
        unsigned int blue);
void Sphere_destroy(Sphere* self);
Vector3D* Sphere_getCentre(const Sphere* self);
double Sphere_getRadius(const Sphere* self);
unsigned int Sphere_getRed(const Sphere* self);
unsigned int Sphere_getGreen(const Sphere* self);
unsigned int Sphere_getBlue(const Sphere* self);
void Sphere_scaleColors(struct Sphere* self, double factor); 
#endif
