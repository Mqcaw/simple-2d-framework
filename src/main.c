#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "window.h"
#include "grid.h"
#include "cell.h"

Window window;
int size = 50;
int offset = 0;

int sigma = 3;

void update_grid(Grid* grid);
void init_grid(Grid* grid);

int main(int argc, char *argv[]) {

    init_engine();

    SDL_Color bg_color = {32, 32, 32, 0};
    window = create_window("SDL3 Main Grid", 800, 800, bg_color);
    
    Window* windows[] = {&window};
    int num_windows = sizeof(windows) / sizeof(windows[0]);

    Grid grid = create_grid(size, size, 2);

    Grid* grids[] = {&grid};
    int num_grids = sizeof(grids) / sizeof(grids[0]);

    init_grid(&grid);
   
    test_grid_change(&grid, 25, 25);

    while (is_engine_running()) {
        engine_update(windows, num_windows);
        update_grid(&grid);
        render_grid(grid, &window);
    }



    for (int i = 0; i < num_grids; ++i) {
        free_grid(*grids[i]);
    }
    printf("Grid freed successfully.\n");
    cleanup_engine(windows, num_windows);
    printf("Engine cleaned up successfully.\n");
    return 0;
}

void update_grid(Grid* grid) {
    for (int i = 0; i < grid->num_rows; ++i) {
        for (int j = 0; j < grid->num_cols; ++j) {
            if (grid->array[i][j].walkable) {
                grid->array[i][j].color.r = 0;
                grid->array[i][j].color.g = 0;
                grid->array[i][j].color.b = 0;
                grid->array[i][j].color.a = 255;
            } else {
                grid->array[i][j].color.r = 255;
                grid->array[i][j].color.g = 255;
                grid->array[i][j].color.b = 255;
                grid->array[i][j].color.a = 255;
            }
        }
    }

}

void init_grid(Grid* grid) {
    for (int i = 0; i < grid->num_rows; ++i) {
        for (int j = 0; j < grid->num_cols; ++j) {
            //grid->array[i][j].walkable = (rand() / (double)RAND_MAX) < exp(-((i - 25)*(i - 25) + (j - 25)*(j - 25)) / (2.0 * sigma * sigma));
        }
    }
}

void test_grid_change(Grid* grid, int x, int y) {
    for (int i = 0; i < grid->num_rows; ++i) {
        for (int j = 0; j < grid->num_cols; ++j) {
            grid->array[i][j].walkable = (rand() / (double)RAND_MAX) < exp(-((i - x)*(i - x) + (j - y)*(j - y)) / (2.0 * sigma * sigma));
            grid->array[i][j].walkable = !grid->array[i][j].walkable;
        }
    }
}