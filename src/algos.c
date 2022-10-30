//
// Created by Dennis Concepción Martín on 15/10/22.
//

#include "algos.h"

int is_path(unsigned x, unsigned y, png_bytep* pRows) {
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
    unsigned int x = 0;
    unsigned int y = 1;
    char direction = 'R';

    is_path(x, y, pRows);

    while (x < width && y < width) {

        if (x == width - 1 && y == width - 2) {
            break;
        }

        switch (direction) {  // NOLINT(hicpp-multiway-paths-covered)
            case 'R':

                // Check if down position is white
                if (is_path(x, y + 1, pRows)) {
                    ++y;
                    direction = 'D';
                }

                // Check if right position is white
                else if (is_path(x + 1, y, pRows)) {
                    ++x;
                    direction = 'R';
                }

                // Check if up position is white
                else if (is_path(x, y - 1, pRows)) {
                    --y;
                    direction = 'U';
                }

                // Turn 180
                else {
                    --x;
                    direction = 'L';
                }

                break;

            case 'L':

                // Check if up position is white
                if (is_path(x, y - 1, pRows)) {
                    --y;
                    direction = 'U';
                }

                // Check if left position is white
                else if (is_path(x - 1, y, pRows)) {
                    --x;
                    direction = 'L';
                }

                // Check if down position is white
                else if (is_path(x, y + 1, pRows)) {
                    ++y;
                    direction = 'D';
                }

                // Turn 180
                else {
                    ++x;
                    direction = 'R';
                }

                break;

            case 'U':

                // Check if right position is white
                if (is_path(x + 1, y, pRows)) {
                    ++x;
                    direction = 'R';
                }

                // Check if up position is white
                else if (is_path(x, y - 1, pRows)) {
                    --y;
                    direction = 'U';
                }

                // Check if left position is white
                else if (is_path(x - 1, y, pRows)) {
                    --x;
                    direction = 'L';
                }

                // Turn 180
                else {
                    ++y;
                    direction = 'D';
                }

                break;

            case 'D':

                // Check if left position is white
                if (is_path(x - 1, y, pRows)) {
                    --x;
                    direction = 'L';
                }

                // Check if down position is white
                else if (is_path(x, y + 1, pRows)) {
                    ++y;
                    direction = 'D';
                }

                // Check if right position is white
                else if (is_path(x + 1, y, pRows)) {
                    ++x;
                    direction = 'R';
                }

                // Turn 180
                else {
                    --y;
                    direction = 'U';
                }

                break;
        }
    }
}