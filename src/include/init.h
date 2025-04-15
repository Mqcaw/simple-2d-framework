#ifndef INIT_H
#define INIT_H

#include <SDL3/SDL.h>

void window_init(SDL_Window** window, int width, int height);
void renderer_init(SDL_Renderer** renderer, SDL_Window** window);

#endif //INIT_H