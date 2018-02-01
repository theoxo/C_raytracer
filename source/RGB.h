typedef struct RGB RGB;
void RGB_init(RGB* self, unsigned int red, unsigned int green, unsigned int blue);
RGB* RGB_create(unsigned int red, unsigned int green, unsigned int blue);
void RGB_destroy(RGB* self); 
unsigned int RGB_getRed(RGB* self);
unsigned int RGB_getGreen(RGB* self); 
unsigned int RGB_getBlue(RGB* self); 
RGB* RGB_copy(RGB* source);
