#ifndef ENGINE_H
#define ENGINE_H

// Include necessary standard libraries
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "window.h"
#include "grid.h"

// Function declarations
bool init_engine();
void render_grid(Grid grid,Window* window);
void engine_update(Window* windows[], int num_windows);
bool is_engine_running();
void cleanup_engine(Window* windows[], int num_windows);

#endif // ENGINE_H