#ifndef RGB_H
#define RGB_H
#include "RGB.h"
typedef struct RGB {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
} RGB;
void RGB_init(RGB* self, unsigned int red, unsigned int green, unsigned int blue);
RGB* RGB_create(unsigned int red, unsigned int green, unsigned int blue);
void RGB_destroy(RGB* self); 
unsigned int RGB_getRed(const RGB* self);
unsigned int RGB_getGreen(const RGB* self); 
unsigned int RGB_getBlue(const RGB* self); 
RGB* RGB_copy(const RGB* source);
#endif
