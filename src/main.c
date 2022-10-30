#include <time.h>
#include "process.h"
#include "algos.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Incorrect arguments\n");
        error();
    }

    char* filename = argv[1];
    struct PngInfo png_info = read_png(filename);

    printf("Filename: %s\n", png_info.filename);
    printf("Width: %d\n", png_info.width);
    printf("Height: %d\n", png_info.height);

    clock_t start = clock();
    wall_follower(png_info.rows, png_info.width);
    clock_t end = clock();

    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Algorithm duration: %f seconds\n", time_taken);

    write_png(png_info);

    return 0;
}