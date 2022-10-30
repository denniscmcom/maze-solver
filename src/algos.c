//
// Created by Dennis Concepción Martín on 15/10/22.
//

#include "algos.h"

int is_path(int x, int y, png_bytep* pRows) {
    png_byte *pRow = pRows[y];
    png_byte *pPixel = &pRow[x * 4];

    if (pPixel[0] == 255) {     // pPixel[0] -> R
        pPixel[1] = 0;          // pPixel[1] -> G
        pPixel[2] = 0;          // pPixel[2] -> B

        return 1;
    } else {
        return 0;
    }
}

void wall_follower(png_bytep* pRows, unsigned int width) {
    int x = 0;
    int y = 1;

    enum { R, L, U, D } direction = R;

    static const struct {
        int dx, dy, next;
    } lut[][4] = {
            [R] = {{+0, +1, D}, {+1, +0, R}, {+0, -1, U}, {-1, +0, L}},
            [L] = {{+0, -1, U}, {-1, +0, L}, {+0, +1, D}, {+1, +0, R}},
            [U] = {{+1, +0, R}, {+0, -1, U}, {-1, +0, L}, {+0, +1, D}},
            [D] = {{-1, +0, L}, {+0, +1, D}, {+1, +0, R}, {+0, -1, U}},
    };

    is_path(x, y, pRows);

    while (x < width && y < width) {

        if (x == width - 1 && y == width - 2) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int tx = x + lut[direction][i].dx;
            int ty = y + lut[direction][i].dy;

            if (is_path(tx, ty, pRows)) {
                x = tx;
                y = ty;
                direction = lut[direction][i].next;
                break;
            }
        }
    }
}