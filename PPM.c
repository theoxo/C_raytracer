#include <stdio.h>
#include "RGB.h"

int PPM_save(RGB*** pixel_array, char* file_name, unsigned int height, unsigned int width) {

    FILE* image = fopen(file_name, "r");
    
    if (image == NULL) {
        printf("PPM_save: Failed to allocate file.\n");
        return 0;
    }

    fprintf(image, "P3\n%u %u\n255\n", width, height);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            fprintf(image, "%d ", RGB_getRed(pixel_array[i][j]));
            fprintf(image, "%d ", RGB_getGreen(pixel_array[i][j]));
            fprintf(image, "%d ", RGB_getBlue(pixel_array[i][j]));
        }
        fprintf(image, "\n");
    }

    // Done writing. Close
    fclose(image);

    return 1;
}
    
