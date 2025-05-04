#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include "engine.h"
#include "window.h"
#include "grid.h"
#include "cell.h"
#include "input_manager.h"
#include "entity.h"

#define TICK_RATE 240
#define TICK_TIME_SEC (1 / TICK_RATE)

InputBuffer input_buffer;
Window window;

int size = 50;
int offset = 0;
int sigma = 3;

void* engine_loop(void* arg);
void* render_loop(void* arg);
void tick_grid(Grid* grid);
void init_grid(Grid* grid);
void process_inputs(InputBuffer* input_buffer, Grid* grid);
void test_grid_change(Grid* grid, int x, int y);
void test();
double now();

int main(int argc, char *argv[]) {

    input_manager_init(&input_buffer, 16);
    init_engine();


    SDL_Color bg_color = {32, 32, 32, 0};
    window = create_window("SDL3 Main Grid", 800, 800, bg_color);
    
    Window* windows[] = {&window};
    int num_windows = sizeof(windows) / sizeof(windows[0]);

    Grid grid = create_grid(size, size, 2);

    Grid* grids[] = {&grid};
    int num_grids = sizeof(grids) / sizeof(grids[0]);

    init_grid(&grid);

    
    Entity entity;
    entity.cell.x = 10;
    entity.cell.y = 10;
    entity.cell.color.r = 255;
    entity.cell.color.g = 0;
    entity.cell.color.b = 0;
    entity.cell.color.a = 255;

    Entity* entities[] = {&entity};
    int num_entities = sizeof(entities) / sizeof(entities[0]);

    double accumulator = 0.0;
    double lastUpdate = now();
    double delta;

    while (is_engine_running()) {
        double current = now();
        delta = current - lastUpdate;
        lastUpdate = current;

        accumulator += delta;

        if (accumulator >= TICK_TIME_SEC) {
            engine_update(windows, num_windows, &input_buffer);
            process_inputs(&input_buffer, &grid);
            tick_grid(&grid);
            accumulator -= TICK_TIME_SEC;
        }

        render(grid, entities, num_entities, &window);
    }


    input_manager_free(&input_buffer);
    for (int i = 0; i < num_grids; ++i) {
        free_grid(*grids[i]);
    }
    printf("Grid freed successfully.\n");
    cleanup_engine(windows, num_windows);
    printf("Engine cleaned up successfully.\n");
    return 0;
}

void tick_grid(Grid* grid) {
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

void process_inputs(InputBuffer* input_buffer, Grid* grid) {
    for (size_t i = 0; i < input_buffer->count; ++i) {
        const SDL_Event* event = &input_buffer->events[i];

        // FIFO: process events in order
        switch (event->type) {
            case SDL_EVENT_KEY_DOWN:
                if (event->key.key == SDLK_LEFT) {
                    printf("Move left\n");
                }

                break;
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                printf("Mouse button pressed at (%f, %f)\n", event->button.x, event->button.y);
                test_grid_change(grid, event->button.x, event->button.y);

        break;
            case SDL_EVENT_MOUSE_MOTION:
                //printf("Mouse move (%f, %f)\n", event->button.x, event->button.y);
                break;
            case SDL_EVENT_QUIT:
                printf("Quit requested\n");
                break;

            default:
                break;
        }
        input_manager_remove_first(input_buffer);
    }
}

void test_grid_change(Grid* grid, int x, int y) {
    int x_2 = round((double) x / 800 * 50);
    int y_2 = round((double) y / 800 * 50);
    for (int i = 0; i < grid->num_rows; ++i) {
        for (int j = 0; j < grid->num_cols; ++j) {
            // Compute probability based on Gaussian centered at (x, y)
            double prob = exp(-((i - x_2)*(i - x_2) + (j - y_2)*(j - y_2)) / (2.0 * sigma * sigma));
            // Flip walkability with some probability
            if ((rand() / (double)RAND_MAX) < prob) {
                //grid->array[j][i].walkable = !grid->array[j][i].walkable;
                grid->array[j][i].walkable = 0;
            }
        }
    }
}

double now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}