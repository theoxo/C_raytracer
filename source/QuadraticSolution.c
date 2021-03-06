#include <stdio.h>
#include <stdlib.h>

/**
 * Source file for QuadraticSolution.
 * Note "positive" and "negative" does not refer
 * to the actual signs of the numbers, but the way in which
 * they were derived (i.e. in the "plus-minus" part of the quadratic formula)
 */
struct QuadraticSolution {
    double positive;
    double negative;
};

// Initiliaze values but do not allocate memory
void QuadraticSolution_init(struct QuadraticSolution* self, double pos, double neg) {
    if (self == NULL) {
        printf("QuadraticSolution_init: self is null.\n");
        return;
    }

    self->positive = pos;
    self->negative = neg;
}

// Initiliazation with allocation
struct QuadraticSolution* QuadraticSolution_create(double pos, double neg) {
    struct QuadraticSolution* qs = (struct QuadraticSolution*) malloc(sizeof(struct QuadraticSolution));

    if (qs == NULL) {
        printf("QuadraticSolution_create: malloc failed; out of memory?\n");
        return NULL;
    }

    QuadraticSolution_init(qs, pos, neg);
    return qs;
}

void QuadraticSolution_destroy(struct QuadraticSolution* self) {
    if (self != NULL) {
        free(self);
    }
}

double QuadraticSolution_getPositive(const struct QuadraticSolution* qs) {
    if (qs == NULL) {
        printf("QuadraticSolution_getPositive: null pointer as parameter.\n");
        return -1;
    }

    return qs->positive;
}

double QuadraticSolution_getNegative(const struct QuadraticSolution* qs) {
    if (qs == NULL) {
        printf("QuadraticSolution_getNegative: null pointer as parameter.\n");
        return -1;
    }

    return qs->negative;
}

