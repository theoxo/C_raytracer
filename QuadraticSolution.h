struct QuadraticSolution;
void QuadraticSolution_init(QuadraticSolution* self, double pos, double neg);
QuadraticSolution* QuadraticSolution_create(double pos, double neg);
void QuadraticSolution_destroy(QuadraticSolution* self);
double QuadraticSolution_getPositive(QuadraticSolution* qs);
double QuadraticSolution_getNegative(QuadraticSolution* qs);

