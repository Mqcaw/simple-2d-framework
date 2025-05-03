#include "window.h"

Window create_window(char* title, int width, int height, SDL_Color bg_color) {
    Window window;
    window.title = title;
    window.init_width = width;
    window.init_height = height;
    window.bg_color = bg_color;

    window.window = SDL_CreateWindow(window.title, window.init_width, window.init_height, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_TRANSPARENT);
    if (!window.window) {
        SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
    }

    window.renderer = SDL_CreateRenderer(window.window, NULL);
    if (!window.renderer) {
        SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_DestroyWindow(window.window);
        SDL_Quit();
    }
    SDL_SetRenderDrawBlendMode(window.renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(window.renderer, 0, 0, 0, 255);
    SDL_RenderClear(window.renderer);
    SDL_RenderPresent(window.renderer);

    return window;

}