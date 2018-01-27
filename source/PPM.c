#include <stdio.h>
#include <stdlib.h>
#include "RGB.h"

// NB: DESTROYS supplied pixel_array
int PPM_save(RGB*** pixel_array, char* file_name, unsigned int height, unsigned int width) {

    FILE* image = fopen(file_name, "w+");
    
    if (image == NULL) {
        printf("PPM_save: Failed to allocate file.\n");
        return 0;
    }

    fprintf(image, "P3\n%u %u\n255\n", width, height);

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            fprintf(image, "%u ", RGB_getRed(pixel_array[i][j]));
            fprintf(image, "%u ", RGB_getGreen(pixel_array[i][j]));
            fprintf(image, "%u ", RGB_getBlue(pixel_array[i][j]));
             
            // Destroy pixel
            RGB_destroy(pixel_array[i][j]);
        }

        free(pixel_array[i]);
        fprintf(image, "\n");
    }

    // Done writing. Close
    free(pixel_array);
    fclose(image);

    return 1;
}
    
