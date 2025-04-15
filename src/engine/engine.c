#include <stdio.h>

#include <SDL3/SDL.h>
#include "engine.h"
#include "init.h"
#include "cell.h"
#include "grid.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
int g_width = 800;
int g_height = 600;
uint8_t g_rows = 50;
uint8_t g_cols = 50;

void engine_init() {
    printf("Engine starting\n");

    window_init(&g_window, g_width, g_height);
    renderer_init(&g_renderer, &g_window);

    SDL_HideCursor();

    printf("Engine started\n");
}


void engine_exit() {
    printf("Exiting engine\n");
    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    printf("Engine exited\n");
}

void engine_sleep(int seconds) {
    printf("Engine sleep start\n");
    for (int i = 0; i < seconds; i++) {
        printf("%i\n", i);
        SDL_Delay(seconds * 1000);
    }
    printf("%i\n", seconds);
    printf("Engine sleep end\n");
}

Grid engine_create_new_grid() {
    return create_grid(g_rows, g_cols);
}

void engine_free_grid(Grid grid) {
    free_grid(grid);
}

void engine_print_grid(Grid grid) {
    for (int i = 0; i < grid.num_rows; ++i) {

        for (int j = 0; j < grid.num_cols; ++j) {
            printf("%i ", grid.array[i][j].walkable);
        }
        printf("\n");
    }
}