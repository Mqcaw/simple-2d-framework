#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>
#include <SDL3/SDL.h>

typedef struct Window{
    char *title;
    int init_width; 
    int init_height;
    int width;
    int height;
    SDL_Color bg_color;
    SDL_Window *window;
    SDL_Renderer *renderer;
} Window;

Window create_window(char* title, int width, int height, SDL_Color bg_color);

#endif // WINDOW_H