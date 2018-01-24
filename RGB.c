#include <stdlib.h>
#include <stdio.h>

typedef struct RGB {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
} RGB;

void RGB_init(RGB* self, unsigned int red, unsigned int green, unsigned int blue) {
    if (self == NULL) {
        printf("RGB_init: supplied parameter self is NULL pointer.\n");
        return;
    }

    self->red = red;
    self->green = green;
    self->blue = blue;
}

RGB* RGB_create(unsigned int red, unsigned int green, unsigned int blue) {
    RGB* result = (RGB*) malloc(sizeof(RGB));
    
    if (result == NULL) {
        printf("RGB_create: result is NULL. Out of memory?\n");
        return NULL;
    }

    RGB_init(result, red, green, blue);
    return result;
}

void RGB_destroy(RGB* self) {
    if (self != NULL) {
        free(self);
    }
}

unsigned int RGB_getRed(RGB* self) {
    if (self == NULL) {
        printf("RGB_getRed: supplied self is null.\n");
        return 0;
    }
    return self->red;
}

unsigned int RGB_getGreen(RGB* self) {
    if (self == NULL) {
        printf("RGB_getGreen: supplied self is null.\n");
        return 0;
    }
    return self->green;
}

unsigned int RGB_getBlue(RGB* self) {
    if (self == NULL) {
        printf("RGB_getBlue: supplied self is null.\n");
        return 0;
    }
    return self->blue;
}
