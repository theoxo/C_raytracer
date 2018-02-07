/*
 * LightPhysics source file
 * Theo Olausson
 * 23/01/18
 */
#include "QuadraticSolution.h"
#include "Vector3D.h"
#include "Sphere.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Calculates the reflected vector based on the incident vector and the surface normal
Vector3D* LightPhysics_reflection(Vector3D* incident, Vector3D* surface_normal) {
   
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
Vector3D* LightPhysics_refraction(Vector3D* incident, Vector3D* surface_normal, 
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

QuadraticSolution* LightPhysics_ray_sphere_intersection(Sphere* sphere, Vector3D* ray_origin, Vector3D* ray_direction) {

    
    Vector3D origin_minus_centre = Vector3D_difference(ray_origin, Sphere_getCentre(sphere));

    double a = Vector3D_dot(ray_direction, ray_direction);
    Vector3D ray_direction_times_two = Vector3D_multiply(ray_direction, 2);

    double b = Vector3D_dot(&ray_direction_times_two, &origin_minus_centre);
    double c = Vector3D_dot(&origin_minus_centre, &origin_minus_centre) - pow(Sphere_getRadius(sphere), 2);

    double in_sqrt = pow(b, 2) - 4*a*c;
    
    double pos = 0;
    double neg = 0;
    if (in_sqrt >= 0) {
        pos = ( -b + sqrt(pow(b,2) - 4*a*c) ) / (2*a);
        neg = ( -b - sqrt(pow(b,2) - 4*a*c) ) / (2*a);
    } else {
        // Non-real solution.
        // Returning 0,0 is good enough for our purposes
    }
    
    QuadraticSolution* result = QuadraticSolution_create(pos, neg);


    return result;
}

