#ifndef ENGINE_H
#define ENGINE_H

// Include necessary standard libraries
#include <stdbool.h>
#include <SDL3/SDL.h>
#include "window.h"
#include "grid.h"
#include "input_manager.h"
#include "entity.h"

// Function declarations
bool init_engine();
void render(Grid grid, Entity* entities[], int num_entities, Window* window);
void engine_update(Window* windows[], int num_windows, InputBuffer* input_buffer);
bool is_engine_running();
void engine_stop();
void cleanup_engine(Window* windows[], int num_windows);

#endif // ENGINE_H