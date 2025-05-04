#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <stdbool.h>
#include "cell.h"


typedef struct Entity{
    Cell cell;
    float x;
    float y;
} Entity;

#endif // ENTITY_H