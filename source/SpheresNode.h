/*
 * Header file for (singly linked) list of spheres
 * Theo Olausson
 * 27/01/18
 */
#ifndef SPHERE_H
#define SPHERE_H
#include "Sphere.h"
#endif

typedef struct SpheresNode SpheresNode;

void SpheresNode_init(SpheresNode* self, Sphere* sphere); 
SpheresNode* SpheresNode_create(Sphere* sphere);
void SpheresNode_destroyAll();
void SpheresNode_add(Sphere* sphere);
SpheresNode* SpheresNode_getTail();
