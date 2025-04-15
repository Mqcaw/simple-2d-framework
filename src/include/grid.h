#ifndef GRID_H
#define GRID_H

#include <stdint.h>
#include "cell.h"

typedef struct Grid{
    Cell** array;
    uint8_t num_rows;
    uint8_t num_cols;
} Grid;

Grid create_grid(uint8_t rows, uint8_t cols);
void free_grid(Grid grid);

#endif // GRID_H