/*
 * 3D-Vector header file
 * Theo Olausson
 * 23/01/18
 */

typedef struct Vector3D Vector3D;
Vector3D* Vector3D_create(double x, double y, double z);
void Vector3D_destroy(Vector3D* self);
double Vector3D_getX(Vector3D* self);
double Vector3D_getY(Vector3D* self);
double Vector3D_getZ(Vector3D* self);
Vector3D* Vector3D_copy(Vector3Dr* source);
double Vector3D_dot(Vector3D* a, Vector3D* b);
double Vector3D_magnitude(Vector3D* self);
Vector3D* Vector3D_difference(Vector3D* a, Vector3D* b);
Vector3D* Vector3D_multiply(Vector3D* vec, double factor);

