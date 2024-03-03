cmake_minimum_required(VERSION 3.23)
project(maze_solver C)

set(LIBPNG_DIR /usr/local/Cellar/libpng/1.6.43)     # Set LIBPNG_DIR var to library path
include_directories(${LIBPNG_DIR}/include)          # Add include folder
link_directories(${LIBPNG_DIR}/lib)                 # Link lib folder

set(CMAKE_C_STANDARD 99)

add_executable(maze_solver src/main.c src/algos.c src/algos.h src/process.c src/process.h src/handlers.c src/handlers.h)

target_link_libraries(maze_solver png)              # Link libraries
