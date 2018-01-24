typedef struct RGB RGB;
void RGB_init(struct RGB* self, double red, double green, double blue);
struct RGB* RGB_create(double red, double green, double blue);
void RGB_destroy(struct RGB* self); 
double RGB_getRed(struct RGB* self);
double RGB_getGreen(struct RGB* self); 
double RGB_getBlue(struct RGB* self); 
