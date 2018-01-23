/*
 * LightPhysics source file
 * Theo Olausson
 * 23/01/18
 */

#include "QuadraticSolution.h"
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

// Calculates the refracted vector. Takes
// an incident vector, a surface normal vector,
// and the refractive indices gamma1 and gamma2 of 
// the original and new medium, respectively
Vector3D* LightPhysics_refraction(3DVector* incident, 3DVector surface_normal, 
        double gamma1, double gamma2) {

    double gamma = gamma1 / gamma2;
    double c1 = Vector3D_dot(incident, surface_normal);
    double c2 = sqrt( 1 - pow(gamma, 2) * (1 - pow(c1, 2)) );


    double x = ( gamma * Vector3D_getX(incident) )
              + ( ( gamma * c1 - c2 )
                  * Vector3D_getX(surface_normal) 
                );

    double y = ( gamma * Vector3D_getY(incident) )
              + ( ( gamma * c1 - c2 )
                  * Vector3D_getY(surface_normal) 
                );

    double z = ( gamma * Vector3D_getZ(incident) )
              + ( ( gamma * c1 - c2 )
                  * Vector3D_getZ(surface_normal) 
                );

    Vector3D* result = Vector3D_create(x, y, z);
    
    return result;
}

QuadraticSolution* LightPhysics_ray_sphere_intersection(Vector3D* sphere_centre, double radius,
        Vector3D* ray_origin, Vector3D* ray_direction) {

    Vector3D* origin_minus_centre = Vector3D_difference(ray_origin, sphere_centre);

    double a = Vector3D_dot(ray_direction, ray_direction);
    double b = Vector3D_dot( Vector3D_multiply(ray_direction, 2), origin_minus_centre );
    double c = Vector3D_dot(origin_minus_centre, origin_minus_centre) - pow(radius, 2);

    double pos = ( -b + sqrt(pow(b,2) - 4*a*c) ) / (2*a);
    double neg = ( -b - sqrt(pow(b,2) - 4*a*c) ) / (2*a);
    
    QuadraticSolution* result = QuadraticSolution_create(pos, neg);

    Vector3D_destroy(origin_minus_centre);

    return result;
}

