//
// Created by Dennis Concepción Martín on 18/10/22.
//

#ifndef MAZE_SOLVER_PROCESS_H
#define MAZE_SOLVER_PROCESS_H

#include <png.h>
#include "handlers.h"

struct PngInfo {
    char* filename;
    unsigned int width, height;
    png_bytep* rows;
    png_byte byte_depth, color_type;
};

struct PngInfo read_png(char* filename);
void write_png(struct PngInfo);

#endif //MAZE_SOLVER_PROCESS_H
