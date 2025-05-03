#ifndef GRID_H
#define GRID_H

#include <stdint.h>
#include <SDL3/SDL.h>
#include "cell.h"

typedef struct Grid{
    Cell** array;
    int num_rows;
    int num_cols;
    int spacing;
} Grid;

Grid create_grid(int rows, int cols, int spacing);
void free_grid(Grid grid);
void print_grid(Grid grid);

#endif // GRID_H