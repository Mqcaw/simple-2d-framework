#include <SDL3/SDL.h>
#include <stdio.h>

void window_init(SDL_Window** window, int width, int height) {
    *window = SDL_CreateWindow("Game", width, height, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    SDL_SetWindowPosition(*window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    if (*window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
    } else {
        printf("Window created\n");
    }
}

void renderer_init(SDL_Renderer** renderer, SDL_Window** window) {
    *renderer = SDL_CreateRenderer(*window, "opengl");

    if (*renderer == NULL) {
        printf("Renderer could not be created: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
    } else {
        printf("Renderer created\n");
    }
}