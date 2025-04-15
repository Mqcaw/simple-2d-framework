#include <stdio.h>
#include <stdlib.h>

#include "cell.h"
#include "grid.h"


Grid create_grid(uint8_t rows, uint8_t cols) {
    Grid grid;
    grid.array = (Cell**)malloc(rows * sizeof(Cell *));
    grid.num_rows = rows;
    grid.num_cols = cols;

    for (int i = 0; i < grid.num_rows; ++i) {
        grid.array[i] = (Cell*)malloc(grid.num_cols * sizeof(Cell));
        if (grid.array[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        for (int j = 0; j < grid.num_cols; ++j) {
            grid.array[i][j].walkable = 1;
            grid.array[i][j].x = j;
            grid.array[i][j].y = i;
        }
    }
    return grid;
}

void free_grid(Grid grid) {
    for (int i = 0; i < grid.num_cols; ++i) {
        free(grid.array[i]);
    }
    free(grid.array);
}