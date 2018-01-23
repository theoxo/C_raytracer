
/*
 * LightPhysics source file
 * Theo Olausson
 * 23/01/18
 */

3DVector* LightPhysics_reflection(3DVector* incident, 3DVector* surface_normal) {
   
    double x = 3DVector_getX(incident) - ( 2 * 3DVector_dot(incident, surface_normal) 
                * 3DVector_getX(surface_normal) );
