/*
 * 3D-Vector header file
 * Theo Olausson
 * 23/01/18
 */

struct Vector3D;
Vector3D* 3DVector_create(double x, double y, double z);
void Vector3D_destroy(3DVector* self);
double Vector3D_getX(3DVector* self);
double Vector3D_getY(3DVector* self);
double Vector3D_getZ(3DVector* self);
Vector3D* 3DVector_copy(3DVector* source);
double Vector3D_dot(3DVector* a, 3DVector* b);
double Vector3D_magnitude(3DVector* self);
