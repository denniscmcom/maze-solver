//
// Created by Dennis Concepción Martín on 15/10/22.
//

#include "algo.h"

int isWhite(unsigned x, unsigned y, png_bytep* pRows) {
    png_byte *pRow = pRows[y];
    png_byte *pPixel = &pRow[x * 4];

    int r = pPixel[0];
    int g = pPixel[1];
    int b = pPixel[2];

    if (r == 255 && g == 255 && b == 255) {
        return 1;
    } else {
        return 0;
    }
}


void wallFollower(png_bytep* pRows, unsigned int width) {
    unsigned int x = 0;
    unsigned int y = 1;
    char direction = 'R';

    while (x < width && y < width) {

        // Set pixel to color red
        printf("x: %d, y: %d is white\n", x, y);

        if (x == width - 1 && y == width - 2) {
            exit(0);
        }

        switch (direction) {  // NOLINT(hicpp-multiway-paths-covered)
            case 'R':

                // Check if down position is white
                if (isWhite(x, y + 1, pRows)) {
                    ++y;
                    direction = 'D';
                }

                // Check if right position is white
                else if (isWhite(x + 1, y, pRows)) {
                    ++x;
                    direction = 'R';
                }

                // Check if up position is white
                else if (isWhite(x, y - 1, pRows)) {
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
                if (isWhite(x, y - 1, pRows)) {
                    --y;
                    direction = 'U';
                }

                // Check if left position is white
                else if (isWhite(x - 1, y, pRows)) {
                    --x;
                    direction = 'L';
                }

                // Check if down position is white
                else if (isWhite(x, y + 1, pRows)) {
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
                if (isWhite(x + 1, y, pRows)) {
                    ++x;
                    direction = 'R';
                }

                // Check if up position is white
                else if (isWhite(x, y - 1, pRows)) {
                    --y;
                    direction = 'U';
                }

                // Check if left position is white
                else if (isWhite(x - 1, y, pRows)) {
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
                if (isWhite(x - 1, y, pRows)) {
                    --x;
                    direction = 'L';
                }

                // Check if down position is white
                else if (isWhite(x, y + 1, pRows)) {
                    ++y;
                    direction = 'D';
                }

                // Check if right position is white
                else if (isWhite(x + 1, y, pRows)) {
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