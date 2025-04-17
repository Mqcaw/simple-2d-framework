#ifndef INIT_H
#define INIT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>

void window_init(SDL_Window** window, SDL_GLContext* gl_context, int width, int height);

#endif //INIT_H