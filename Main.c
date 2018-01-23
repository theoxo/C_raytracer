#include <stdio.h>
#include <stdlib.h>
#include "QuadraticSolution.h"
#include "Vector3D.h"
#include "LightPhysics.h"

int main(int argc, char* argc[]) {

    if (argc != 2) {
        printf("Usage: ./a.out height width\n");
        return 1;
    }
