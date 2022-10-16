#include "algo.h"

int main(int argc, char* argv[]) {
    char* fileName;
    int numberOfPhases;
    unsigned int width, height;

    png_structp pngStruct;
    png_infop pngInfo;
    png_byte colorType;
    png_byte bitDepth;
    png_bytep* pRows;

    if (argc < 2) {
        printf("Incorrect arguments\n");
        abort();
    }

    // Get user arguments
    fileName = argv[1];

    // Add path to filename
    asprintf(&fileName, "mazes/%s", fileName);

    FILE *fp = fopen(fileName, "rb");

    if (!fp) {
        printf("Error opening image named %s\n", fileName);
        abort();
    }

    // Allocate and initialize a pngStruct for reading PNG file
    pngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!pngStruct) {
        printf("png_create_read_struct failed\n");
        abort();
    }

    // Allocate and initialize a pngInfo structure
    pngInfo = png_create_info_struct(pngStruct);

    if (!pngInfo) {
        printf("png_create_info_struct failed\n");
    }

    /*
     * When libpng encounters an error, it expects to longjmp back to your routine.
     * Therefore, you will need to call setjmp and pass your png_jmpbuf(pngStruct).
     * More about setjmp -> https://es.wikipedia.org/wiki/Setjmp.h
     */

    if (setjmp(png_jmpbuf(pngStruct))) {
        printf("Error during init_io\n");
        abort();
    }

    png_init_io(pngStruct, fp);             // Initialize the default input/output functions for the PNG file
    png_set_sig_bytes(pngStruct, 0);        // Set signature bytes
    png_read_info(pngStruct, pngInfo);      // Read info

    width = png_get_image_width(pngStruct, pngInfo);
    height = png_get_image_height(pngStruct, pngInfo);
    colorType = png_get_color_type(pngStruct, pngInfo);
    bitDepth = png_get_bit_depth(pngStruct, pngInfo);

    numberOfPhases = png_set_interlace_handling(pngStruct);
    png_read_update_info(pngStruct, pngInfo);

    printf("Image width: %d\n", width);
    printf("Image height: %d\n", height);
    printf("Color type: %d\n", colorType);
    printf("Bit depth: %d\n", bitDepth);
    printf("Number of phases: %d\n", numberOfPhases);

    // Read file
    if (setjmp(png_jmpbuf(pngStruct))) {
        printf("Error during read_image");
        abort();
    }

    pRows = (png_bytep*) malloc(sizeof(png_bytep) * height);

    for (int y = 0; y < height; y++) {
        pRows[y] = (png_byte *) malloc(png_get_rowbytes(pngStruct, pngInfo));
    }

    // Read the image into memory
    png_read_image(pngStruct, pRows);
    fclose(fp);

    wallFollower(pRows, width);

    // Cleanup heap allocation
    for (int y = 0; y < height; y++) {
        free(pRows[y]);
    }

    free(pRows);

    return 0;
}