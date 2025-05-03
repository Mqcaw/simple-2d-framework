#include <SDL3/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "engine.h"
#include "window.h"
#include "grid.h"
#include "cell.h"


#define TICK_RATE 20
#define TICK_TIME_MS (1000 / TICK_RATE)

bool engine_running = false;



bool init_engine() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    srand(time(NULL));

    engine_running = true;
    return engine_running;
}


void render_grid(Grid grid, Window* window) {
    SDL_SetRenderDrawColor(window->renderer, window->bg_color.r, window->bg_color.g, window->bg_color.b, window->bg_color.a);
    SDL_RenderClear(window->renderer);

    int border = 0;

    int cellWidth = (window->width) / grid.num_cols;
    int cellHeight = (window->height) / grid.num_rows;

    for (int row = 0; row < grid.num_rows; ++row) {
        for (int col = 0; col < grid.num_cols; ++col) {
            SDL_SetRenderDrawColor(window->renderer, grid.array[row][col].color.r, grid.array[row][col].color.g, grid.array[row][col].color.b, grid.array[row][col].color.a);
            SDL_FRect cell = {col * cellWidth, row * cellHeight, cellWidth - grid.spacing, cellHeight - grid.spacing};
            SDL_RenderFillRect(window->renderer, &cell);
        }
    }

    SDL_RenderPresent(window->renderer);
}


void engine_update(Window* windows[], int num_windows) {
    if (!engine_running) {
        cleanup_engine(windows, num_windows);
    }

    for (int i = 0; i < num_windows; ++i) {
        SDL_GetWindowSize(windows[i]->window, &windows[i]->width, &windows[i]->height);
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            engine_running = false;
        } else if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
                for (int i = 0; i < num_windows; ++i) {
                    if (event.window.windowID == SDL_GetWindowID(windows[i]->window)) {
                        if (windows[i]->renderer) SDL_DestroyRenderer(windows[i]->renderer);
                        if (windows[i]->window) SDL_DestroyWindow(windows[i]->window);
                        windows[i]->renderer = NULL;
                        windows[i]->window = NULL;
                        break;
                    }
                }
        }
    }
    SDL_Delay(TICK_TIME_MS);
}

bool is_engine_running() {
    return engine_running;
}

void cleanup_engine(Window* windows[], int num_windows) {
    engine_running = false;
    for (int i = 0; i < num_windows; ++i) {
        if (windows[i]->renderer) SDL_DestroyRenderer(windows[i]->renderer);
        if (windows[i]->window) SDL_DestroyWindow(windows[i]->window);
    }
    SDL_Quit();
}
