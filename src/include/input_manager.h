#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL3/SDL.h>
#include <stddef.h>

typedef struct {
    SDL_Event* events;      // Event array
    size_t count;           // Current number of events in the buffer
    size_t capacity;        // Maximum number of events buffer can hold
} InputBuffer;

void input_manager_init(InputBuffer *input_buffer, size_t initial_capacity);
void input_manager_add(InputBuffer *input_buffer, SDL_Event event);
void input_manager_remove_first(InputBuffer *input_buffer);
void input_manager_free(InputBuffer *input_buffer);

#endif //INPUT_MANAGER_H