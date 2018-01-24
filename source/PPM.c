#include <stdio.h>
#include "RGB.h"

int PPM_save(RGB*** pixel_array, char* file_name, unsigned int height, unsigned int width) {

    FILE* image = fopen(file_name, "a");
    
    if (image == NULL) {
        printf("PPM_save: Failed to allocate file.\n");
        return 0;
    }

    fprintf(image, "P3\n%u %u\n255\n", width, height);

    printf("\n------------------\nImage matrix:\n-------\n");

    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            fprintf(image, "%u ", RGB_getRed(pixel_array[i][j]));
            fprintf(image, "%u ", RGB_getRed(pixel_array[i][j]));
            fprintf(image, "%u ", RGB_getGreen(pixel_array[i][j]));

            printf("%u ", RGB_getBlue(pixel_array[i][j]));
            printf("%u ", RGB_getGreen(pixel_array[i][j]));
            printf("%u ", RGB_getBlue(pixel_array[i][j]));
        }
        fprintf(image, "\n");
        printf("\n");
    }

    // Done writing. Close
    fclose(image);

    return 1;
}
    