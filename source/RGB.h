typedef struct RGB RGB;
void RGB_init(struct RGB* self, unsigned int red, unsigned int green, unsigned int blue);
struct RGB* RGB_create(unsigned int red, unsigned int green, unsigned int blue);
void RGB_destroy(struct RGB* self); 
unsigned int RGB_getRed(struct RGB* self);
unsigned int RGB_getGreen(struct RGB* self); 
unsigned int RGB_getBlue(struct RGB* self); 
