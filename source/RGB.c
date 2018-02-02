#include <stdio.h>
#include <stdlib.h>

struct RGB {
    unsigned int red;
    unsigned int green;
    unsigned int blue;
};

void RGB_init(struct RGB* self, unsigned int red, unsigned int green, unsigned int blue) {
    if (self == NULL) {
        printf("RGB_init: supplied parameter self is NULL pointer.\n");
        return;
    }

    self->red = red;
    self->green = green;
    self->blue = blue;
}

struct RGB* RGB_create(unsigned int red, unsigned int green, unsigned int blue) {
    struct RGB* result = (struct RGB*) malloc(sizeof(struct RGB));
    
    if (result == NULL) {
        printf("RGB_create: result is NULL. Out of memory?\n");
        return NULL;
    }

    RGB_init(result, red, green, blue);
    return result;
}

void RGB_destroy(struct RGB* self) {
    if (self != NULL) {
        free(self);
    }
}

unsigned int RGB_getRed(struct RGB* self) {
    if (self == NULL) {
        printf("RGB_getRed: supplied self is null.\n");
        return 0;
    }
    return self->red;
}

unsigned int RGB_getGreen(struct RGB* self) {
    if (self == NULL) {
        printf("RGB_getGreen: supplied self is null.\n");
        return 0;
    }
    return self->green;
}

unsigned int RGB_getBlue(struct RGB* self) {
    if (self == NULL) {
        printf("RGB_getBlue: supplied self is null.\n");
        return 0;
    }
    return self->blue;
}

struct RGB* RGB_copy(struct RGB* source) {
    if (source != NULL) {
        double red = RGB_getRed(source);
        double green = RGB_getGreen(source);
        double blue = RGB_getBlue(source);

        struct RGB* result = RGB_create(red, green, blue);

        return result;
    } else {
        printf("RGB_copy: passed source parameter is null.\n");
        return NULL;
    }
}
