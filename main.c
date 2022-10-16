#include "algo.h"

int main(int argc, char* argv[]) {
    char* unsolvedFilename;
    char* solvedFilename;
    int phases;
    unsigned int width, height;

    clock_t start, end;
    double cpuTimeUsed;

    FILE* unsolvedFp;
    png_structp unsolvedPngStruct;
    png_infop unsolvedPngInfo;
    png_byte colorType;
    png_byte bitDepth;
    png_bytep* pRows;

    FILE* solvedFp;
    png_structp solvedPngStruct;
    png_infop solvedPngInfo;

    start = clock();

    if (argc < 2) {
        printf("Incorrect arguments\n");
        abort();
    }

    // Get user arguments
    unsolvedFilename = argv[1];

    /*
     * READ FILE
     */

    // Add path to unsolvedFilename
    asprintf(&unsolvedFilename, "mazes/%s", unsolvedFilename);

    // Open file
    unsolvedFp = fopen(unsolvedFilename, "rb");

    if (!unsolvedFp) {
        printf("Error opening image named %s\n", unsolvedFilename);
        abort();
    }

    // Allocate and initialize a unsolvedPngStruct for reading PNG file
    unsolvedPngStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!unsolvedPngStruct) {
        printf("png_create_read_struct failed\n");
        abort();
    }

    // Allocate and initialize a unsolvedPngInfo structure
    unsolvedPngInfo = png_create_info_struct(unsolvedPngStruct);

    if (!unsolvedPngInfo) {
        printf("png_create_info_struct failed\n");
        abort();
    }

    /*
     * When libpng encounters an error, it expects to longjmp back to your routine.
     * Therefore, you will need to call setjmp and pass your png_jmpbuf(unsolvedPngStruct).
     * More about setjmp -> https://es.wikipedia.org/wiki/Setjmp.h
     */

    if (setjmp(png_jmpbuf(unsolvedPngStruct))) {
        printf("Error during init_io\n");
        abort();
    }

    png_init_io(unsolvedPngStruct, unsolvedFp);             // Initialize the default input/output functions for the PNG file
    png_set_sig_bytes(unsolvedPngStruct, 0);        // Set signature bytes
    png_read_info(unsolvedPngStruct, unsolvedPngInfo);      // Read info

    width = png_get_image_width(unsolvedPngStruct, unsolvedPngInfo);
    height = png_get_image_height(unsolvedPngStruct, unsolvedPngInfo);
    colorType = png_get_color_type(unsolvedPngStruct, unsolvedPngInfo);
    bitDepth = png_get_bit_depth(unsolvedPngStruct, unsolvedPngInfo);

    phases = png_set_interlace_handling(unsolvedPngStruct);
    png_read_update_info(unsolvedPngStruct, unsolvedPngInfo);

    printf("Image width: %d\n", width);
    printf("Image height: %d\n", height);
    printf("Color type: %d\n", colorType);
    printf("Bit depth: %d\n", bitDepth);
    printf("Number of phases: %d\n", phases);

    // Read file
    if (setjmp(png_jmpbuf(unsolvedPngStruct))) {
        printf("Error during read_image");
        abort();
    }

    pRows = (png_bytep*) malloc(sizeof(png_bytep) * height);

    for (int y = 0; y < height; y++) {
        pRows[y] = (png_byte *) malloc(png_get_rowbytes(unsolvedPngStruct, unsolvedPngInfo));
    }

    // Read the image into memory
    png_read_image(unsolvedPngStruct, pRows);
    fclose(unsolvedFp);

    /*
     * ALGOS
     */

    wallFollower(pRows, width);

    /*
     * WRITE FILE
     */

    // Add path to unsolvedFilename
    solvedFilename = argv[1];
    asprintf(&solvedFilename, "sols/%s", solvedFilename);

    // Open file
    solvedFp = fopen(solvedFilename, "wb");

    if (!solvedFp) {
        printf("File %s could not be opened for writing", solvedFilename);
        abort();
    }

    // Allocate and initialize a solvedPngStruct for writting PNG file
    solvedPngStruct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!solvedPngStruct) {
        printf("png_create_read_struct failed\n");
        abort();
    }

    // Allocate and initialize a unsolvedPngInfo structure
    solvedPngInfo = png_create_info_struct(solvedPngStruct);

    if (!solvedPngInfo) {
        printf("png_create_info_struct failed\n");
        abort();
    }

    if (setjmp(png_jmpbuf(solvedPngStruct))) {
        printf("Error during init_io\n");
        abort();
    }

    png_init_io(solvedPngStruct, solvedFp);

    // Write header
    if (setjmp(png_jmpbuf(solvedPngStruct))) {
        printf("Error writing header");
        abort();
    }

    png_set_IHDR(solvedPngStruct, solvedPngInfo, width, height, bitDepth, colorType, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE
     );

    png_write_info(solvedPngStruct, solvedPngInfo);

    // Write bytes
    if (setjmp(png_jmpbuf(solvedPngStruct))) {
        printf("Error writing bytes");
        abort();
    }

    png_write_image(solvedPngStruct, pRows);

    // End write
    if (setjmp(png_jmpbuf(solvedPngStruct))) {
        printf("Error during end of write");
        abort();
    }

    png_write_end(solvedPngStruct, NULL);

    // Cleanup heap allocation
    for (int y = 0; y < height; y++) {
        free(pRows[y]);
    }

    free(pRows);
    fclose(solvedFp);

    end = clock();
    cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Maze solved in %f seconds\n", cpuTimeUsed);

    return 0;
}