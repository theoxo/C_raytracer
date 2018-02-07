/*
 * Header file for (singly linked) list of spheres
 * Theo Olausson
 * 27/01/18
 */
#ifndef SPHERESNODE_H
#define SPHERESNODE_H
#include "Sphere.h"
typedef struct SpheresNode SpheresNode;
SpheresNode* SpheresNode_newList(Sphere* sphere);
Sphere* SpheresNode_getSphere(const SpheresNode* node);
void SpheresNode_destroyAllFollowing(SpheresNode* node);
void SpheresNode_add(Sphere* sphere);
SpheresNode* SpheresNode_getTail();
SpheresNode* SpheresNode_getNext(const struct SpheresNode* node);
#endif
