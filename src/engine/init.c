#include <SDL3/SDL.h>
#include <SDL3/SDL_opengl.h>
#include <stdio.h>

void window_init(SDL_Window** window, SDL_GLContext* gl_context, int width, int height) {
    *window = SDL_CreateWindow("OpenGL w/ SDL3", 640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    
    if (*window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
    } else {
        printf("Window created\n");
    }

    *gl_context = SDL_GL_CreateContext(*window);

    glClearColor(255,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(*window);
    
}