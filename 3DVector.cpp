class 3DVector {
  
private:

    double x;
    double y;
    double z;

public:

    3DVector();

    3DVector(double xval, double yval, double zval);

    static double dot(3DVector a, 3DVector b);

    static double magnitude(3DVector a);

    static double reflection(3DVector incident, 3DVector normal);

    double getX();

    double getY();
    
    double getZ();

};

3DVector::getX() { return x }

3DVector::getY() { return y }

3DVector::getZ() { return z }

3DVector::3DVector() { x = 0; y = 0; \ = 0; }

3DVector::3DVector(double xval, double yval, double zval) {   
    x = xval;
    y = yval;
    z = zval;
}

3DVector::dot(3DVector a, 3DVector b) {
    3DVector r(a.getX() * b.getX(), a.getY() * b.getY(), a.getZ() * b.getZ();
