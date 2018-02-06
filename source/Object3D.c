/*
 * Object3D source file
 * For polymorphism of objects
 * Theo Olausson
 * 27/01/18
 */

struct Object3D_vtable {
    struct Object3D* (*new)(struct Object3D *);
    void (*destroy)(struct Object3D *);
}

struct Object3D {
    struct Object3D_vtable* vtable;
    unsigned int type;
}

struct Object3D* new() {
    `
