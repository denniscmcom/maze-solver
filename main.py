import os
import ctypes
import sys

from PIL import Image

PATH = os.getcwd()


def main():
    with Image.open(f'{PATH}/mazes/maze.png') as image:
        width, height = image.size
        pixels = image.load()

    print('')
    print(f'Image name: {sys.argv[1].split(".")[0]}')
    print(f'Image format: {image.format}')
    print(f'Image width: {width} pixels')
    print(f'Image height: {height} pixels')

    matrix = []
    for y in range(height):
        row = []
        for x in range(width):
            r, g, b, _ = pixels[x, y]
            if (r, g, b) == (0, 0, 0):
                row.append(0)
            elif (r, g, b) == (255, 255, 255):
                row.append(1)
            else:
                print(f'Incorrect pixel color at x: {x}, y: {y}')
                exit(1)

        matrix.append(row)

    dll = ctypes.CDLL(f'{PATH}/main.so')
    dll.main.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_char_p)]
    args = (ctypes.c_char * 1)([b'123'])
    dll.main(len(args), args)


if __name__ == '__main__':
    if len(sys.argv) == 2:
        main()
    else:
        print('Incorrect arguments')
