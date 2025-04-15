#ifndef CELL_H
#define CELL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Cell{
    bool walkable;
    uint8_t x;
    uint8_t y;
} Cell;

#endif // CELL_H