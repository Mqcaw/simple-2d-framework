#include <stdlib.h>
#include "input_manager.h"


void input_manager_init(InputBuffer *input_buffer, size_t initial_capacity) {
    input_buffer->events = malloc(initial_capacity * sizeof(SDL_Event));
    input_buffer->count = 0;
    input_buffer->capacity = initial_capacity;
}

void input_manager_add(InputBuffer *input_buffer, SDL_Event event) {
    if (input_buffer->count >= input_buffer->capacity) {
        input_buffer->capacity *= 2; 
        input_buffer->events = realloc(input_buffer->events, input_buffer->capacity * sizeof(SDL_Event));
    }

    input_buffer->events[input_buffer->count++] = event;
}

void input_manager_remove_first(InputBuffer *input_buffer) {
    if (input_buffer->count > 0) {
        for (size_t i = 1; i < input_buffer->count; ++i) {
            input_buffer->events[i - 1] = input_buffer->events[i];
        }
        input_buffer->count--;
    }
}

void input_manager_free(InputBuffer *input_buffer) {
    free(input_buffer->events);
}