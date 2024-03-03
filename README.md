# maze-solver

A maze solver written in C.

## Constraints

-   Only PNG files
-   Mazes should be square
-   Walls should be black `rgb(0, 0, 0)` and path white `rg(255, 255, 255)`
-   Walls and path should be `1px` width
-   The starting point must be at `(x: 0, y: 1)`
-   The ending point should be at `(x: width, y: height - 1)`

## Usage

-   Build executable
-   Make a folder named `mazes` and place your mazes there
-   Make a folder named `sols`. The script place the solutions here
-   Run the program `./maze_solver maze1.png`

## Note

You can use this [website](https://keesiemeijer.github.io/maze-generator/) to generate mazes
