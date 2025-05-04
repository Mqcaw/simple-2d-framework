#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <time.h>
#include "engine.h"
#include "window.h"
#include "grid.h"
#include "cell.h"
#include "input_manager.h"
#include "entity.h"


bool engine_running = false;


bool init_engine() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    srand(time(NULL));

    engine_running = true;
    return engine_running;
}

void render(Grid grid, Entity* entities[], int num_entities, Window* window) {
    SDL_SetRenderDrawColor(window->renderer, window->bg_color.r, window->bg_color.g, window->bg_color.b, window->bg_color.a);
    SDL_RenderClear(window->renderer);

    int cellWidth = (window->width) / grid.num_cols;
    int cellHeight = (window->height) / grid.num_rows;

    for (int row = 0; row < grid.num_rows; ++row) {
        for (int col = 0; col < grid.num_cols; ++col) {
            SDL_SetRenderDrawColor(window->renderer, grid.array[row][col].color.r, grid.array[row][col].color.g, grid.array[row][col].color.b, grid.array[row][col].color.a);
            SDL_FRect cell = {col * cellWidth, row * cellHeight, cellWidth - grid.spacing, cellHeight - grid.spacing};
            SDL_RenderFillRect(window->renderer, &cell);
        }
    }

    for (int i = 0; i < num_entities; i++) {
        SDL_SetRenderDrawColor(window->renderer, entities[i]->cell.color.r, entities[i]->cell.color.g, entities[i]->cell.color.b, entities[i]->cell.color.a);

        int cellWidth = (window->width) / grid.num_cols;
        int cellHeight = (window->height) / grid.num_rows;


        SDL_FRect cell = {entities[i]->cell.x * cellWidth, entities[i]->cell.x * cellHeight, cellWidth - grid.spacing, cellHeight - grid.spacing};
        SDL_RenderFillRect(window->renderer, &cell);
        }

    SDL_RenderPresent(window->renderer);
}



void engine_update(Window* windows[], int num_windows, InputBuffer* input_buffer) {
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
        } else if (event.type == SDL_EVENT_KEY_DOWN) {
            input_manager_add(input_buffer, event);
        } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
            input_manager_add(input_buffer, event);
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            input_manager_add(input_buffer, event);
        }
    }
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