/*
 * Source file for (singly linked) list of spheres
 * Theo Olausson
 * 27/01/18
 */
#include "Sphere.h"
#include <stdlib.h>
#include <stdio.h>

struct SpheresNode {
    struct SpheresNode* next;
    Sphere* sphere;
};

struct SpheresNode* tail = NULL;
struct SpheresNode* head = NULL;

void SpheresNode_init(SpheresNode* self, Sphere* sphere) {
    if (self == NULL || sphere == NULL) {
        printf("ListOfSPheres_init: passed parameter is null.\n");
        return;
    }

    self->sphere = sphere;
}

struct SpheresNode* SpheresNode_newList(Sphere* sphere) {
    if (node == NULL) {
        printf("SpheresNode_newList: given sphere was null.\n");
        return NULL;
    }

    struct SpheresNode* start = SpheresNode_create(sphere);
    tail = start;
    head = start;
    return node;
}

struct SpheresNode* SpheresNode_create(Sphere* sphere) {
    struct SpheresNode node = (struct SphereNode*) malloc(sizeof(struct SpheresNode));

    if (node == NULL) {
        printf("SpheresNode_create: result of malloc is NULL.\n");
        return NULL;
    }

    SpheresNode_init(node, sphere);
    return node;
}

void SpheresNode_destroyAll() {
    while (tail != NULL) {
        struct SpheresNode* next = tail->next;
        free(tail);
        tail = next;
    }

    printf("SpheresNode_destroyAll: List was destroyed.\n");
}

void SpheresNode_add(Sphere* sphere) {
    if (sphere == NULL) {
        printf("SpheresNode_add: given sphere was null.\n");
        return;
    }

    struct SpheresNode* node = SpheresNode_create(sphere);
    head->next = node;
    head = node;
}

struct SpheresNode* SpheresNode_getTail()
    return tail;
}
