/*
 * LightPhysics source file
 * Theo Olausson
 * 23/01/18
 */

#include "Vector3D.h"
#include <math.h>

// Calculates the reflected vector based on the incident vector and the surface normal
Vector3D* LightPhysics_reflection(3DVector* incident, 3DVector* surface_normal) {
   
    double x = Vector3D_getX(incident) 
              - ( 2 * Vector3D_dot(incident, surface_normal) 
                  * Vector3D_getX(surface_normal) 
                );

    double y = Vector3D_getY(incident) 
              - ( 2 * Vector3D_dot(incident, surface_normal) 
                  * Vector3D_getY(surface_normal) 
                );

    double z = Vector3D_getZ(incident) 
              - ( 2 * Vector3D_dot(incident, surface_normal) 
                  * Vector3D_getZ(surface_normal) 
                );

    Vector3D* result = Vector3D_create(x, y, z);
    
    return result;
}


