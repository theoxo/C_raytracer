/*
 * Header file for LightPhysics
 * Source is at LightPhysics.c
 *
 * Theo Olausson
 * 24/01/18
 */
#include "Sphere.h"
Vector3D* LightPhysics_reflection(Vector3D* incident, Vector3D* surface_normal);
Vector3D* LightPhysics_refraction(Vector3D* incident, Vector3D* surface_normal, double gamma1, double gamma2);
QuadraticSolution* LightPhysics_ray_sphere_intersection(Sphere* sphere, Vector3D* ray_origin, Vector3D* ray_direction);
