typedef struct RGB RGB;
void RGB_init(struct RGB* self, double red, double green, double blue) {
    if (self == NULL) {
        printf("RGB_init: supplied parameter self is NULL pointer.\n");
        return;
    }

    self->red = red;
    self->green = green;
    self->blue = blue;
}

struct RGB* RGB_create(double red, double green, double blue) {
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

double RGB_getRed(struct RGB* self) {
    if (self == NULL) {
        printf("RGB_getRed: supplied self is null.\n");
        return 0;
    }
    return self->red;
}

double RGB_getGreen(struct RGB* self) {
    if (self == NULL) {
        printf("RGB_getGreen: supplied self is null.\n");
        return 0;
    }
    return self->green;
}

double RGB_getBlue(struct RGB* self) {
    if (self == NULL) {
        printf("RGB_getBlue: supplied self is null.\n");
        return 0;
    }
    return self->blue;
}
