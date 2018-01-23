#include<stdlib.h>
#include<stdio.h>

/**
 * Source file for QuadraticSolution.
 * Note "positive" and "negative" does not refer
 * to the actual signs of the numbers, but the way in which
 * they were derived (i.e. in the "plus-minus" part of the quadratic formula)
 */
typedef struct QuadraticSolution {
    double positive;
    double negative;
} QuadraticSolution;

// Initiliaze values but do not allocate memory
void QuadraticSolution_init(QuadraticSolution* self, double pos, double neg) {
    if (self == NULL) {
        printf("QuadraticSolution_init: self is null.\n");
        return;
    }

    self->positive = pos;
    self->negative = neg;
}

// Initiliazation with allocation
QuadraticSolution* QuadraticSolution_create(double pos, double neg) {
    QuadraticSolution* qs = (QuadraticSolution*) malloc(sizeof(QuadraticSolution));

    if (vqs == NULL) {
        printf("QuadraticSolution_create: malloc failed; out of memory?\n");
        return NULL;
    }

    QuadraticSolution_init(qs, pos, neg);
    return pos;
}

void QuadraticSolution_destroy(QuadraticSolution* self) {
    if (self != NULL) {
        free(self);
    }
}

double QuadraticSolution_getPositive(QuadraticSolution* qs) {
    if (qs == NULL) {
        printf("QuadraticSolution_getPositive: null pointer as parameter.\n");
        return -1;
    }

    return qs->positive;
}

double QuadraticSolution_getNegative(QuadraticSolution* qs) {
    if (qs == NULL) {
        printf("QuadraticSolution_getNegative: null pointer as parameter.\n");
        return -1;
    }

    return qs->negative;
}

