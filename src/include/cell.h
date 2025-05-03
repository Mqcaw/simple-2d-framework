#ifndef CELL_H
#define CELL_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL3/SDL.h>

typedef struct Cell{
    bool walkable;
    uint8_t x;
    uint8_t y;
    SDL_Color color;
} Cell;

#endif // CELL_H