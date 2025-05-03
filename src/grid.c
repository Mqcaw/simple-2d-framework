#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cell.h"
#include "grid.h"



Grid create_grid(int rows, int cols, int spacing) {
    Grid grid;
    grid.array = (Cell**)malloc(rows * sizeof(Cell *));
    grid.num_rows = rows;
    grid.num_cols = cols;
    grid.spacing = spacing;
    int index = 0;

    for (int i = 0; i < grid.num_rows; ++i) {
        grid.array[i] = (Cell*)malloc(grid.num_cols * sizeof(Cell));
        if (grid.array[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
        }
        for (int j = 0; j < grid.num_cols; ++j) {
            grid.array[i][j].walkable = true;
            index++;
            grid.array[i][j].x = j;
            grid.array[i][j].y = i;
            grid.array[i][j].color.r = 255;
            grid.array[i][j].color.g = 255;
            grid.array[i][j].color.b = 255;
            grid.array[i][j].color.a = 255;
        }
    }
    return grid;
}

void free_grid(Grid grid) {
    for (int i = 0; i < grid.num_rows; ++i) { // Corrected to use num_rows
        free(grid.array[i]);
    }
    free(grid.array);
}

void print_grid(Grid grid) {
    for (int i = 0; i < grid.num_rows; ++i) {
        for (int j = 0; j < grid.num_cols; ++j) {
            printf(" %d", grid.array[i][j].walkable);
        }
        printf("\n");
    }
}
