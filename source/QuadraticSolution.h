#ifndef QUADRATICSOLUTION_H
#define QUADRATICSOLUTION_H
typedef struct QuadraticSolution QuadraticSolution;
void QuadraticSolution_init(QuadraticSolution* self, double pos, double neg);
QuadraticSolution* QuadraticSolution_create(double pos, double neg);
void QuadraticSolution_destroy(QuadraticSolution* self);
double QuadraticSolution_getPositive(const QuadraticSolution* qs);
double QuadraticSolution_getNegative(const QuadraticSolution* qs);
#endif
