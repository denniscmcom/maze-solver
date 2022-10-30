//
// Created by Dennis Concepción Martín on 18/10/22.
//

#include "process.h"

struct PngInfo read_png(char* filename) {
    struct PngInfo png_info;
    png_info.filename = filename;

    asprintf(&filename, "mazes/%s", filename);
    FILE* fp = fopen(filename, "rb");

    if (!fp) {
        error();
    }

    // Allocate and initialize read struct
    png_structp read_struct = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!read_struct) {
        error();
    }

    // Allocate and initialize info struct
    png_infop info_struct = png_create_info_struct(read_struct);

    if (!info_struct) {
        error();
    }

    /*
     * When libpng encounters an error, it expects to longjmp back to your routine.
     * Therefore, you will need to call setjmp and pass your png_jmpbuf(unsolvedPngStruct).
     * More about setjmp -> https://es.wikipedia.org/wiki/Setjmp.h
     */

    if (setjmp(png_jmpbuf(read_struct))) {
        error();
    }

    png_init_io(read_struct, fp);               // Init default input/output functions
    png_set_sig_bytes(read_struct, 0);          // Set signature bytes
    png_read_info(read_struct, info_struct);    // Read info

    // Set struct variables
    png_info.width = png_get_image_width(read_struct, info_struct);
    png_info.height = png_get_image_height(read_struct, info_struct);
    png_info.byte_depth = png_get_bit_depth(read_struct, info_struct);
    png_info.color_type = png_get_color_type(read_struct, info_struct);

    png_read_update_info(read_struct, info_struct);

    // Read file
    if (setjmp(png_jmpbuf(read_struct))) {
        error();
    }

    // Allocate memory dynamically
    png_bytep* rows = (png_bytep*) malloc(sizeof(png_bytep) * png_info.height);
    png_info.rows = rows;

    for (int y = 0; y < png_info.height; y++) {
        rows[y] = (png_byte *) malloc(png_get_rowbytes(read_struct, info_struct));
    }

    // Read image into memory
    png_read_image(read_struct, rows);
    fclose(fp);

    return png_info;
}

void write_png(struct PngInfo png_info) {
    char* solved_filename = png_info.filename;
    asprintf(&solved_filename, "sols/%s", solved_filename);
    FILE* fp = fopen(solved_filename, "wb");

    if (!fp) {
        error();
    }

    // Allocate and initialize write struct
    png_structp write_struct = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!write_struct) {
        error();
    }

    // Allocate and initialize infor struct
    png_infop info_struct = png_create_info_struct(write_struct);

    if (!info_struct) {
        error();
    }

    if (setjmp(png_jmpbuf(write_struct))) {
        error();
    }

    png_init_io(write_struct, fp);

    // Write header
    if (setjmp(png_jmpbuf(write_struct))) {
        printf("Error writing header");
        abort();
    }

    png_set_IHDR(
            write_struct, info_struct, png_info.width, png_info.height, png_info.byte_depth, png_info.color_type,
            PNG_INTERLACE_NONE,PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE
    );

    png_write_info(write_struct, info_struct);

    // Write bytes
    if (setjmp(png_jmpbuf(write_struct))) {
        printf("Error writing bytes");
        abort();
    }

    png_write_image(write_struct, png_info.rows);

    // End write
    if (setjmp(png_jmpbuf(write_struct))) {
        printf("Error during end of write");
        abort();
    }

    png_write_end(write_struct, NULL);

    // Cleanup heap allocation
    for (int y = 0; y < png_info.height; y++) {
        free(png_info.rows[y]);
    }

    free(png_info.rows);
    fclose(fp);
}