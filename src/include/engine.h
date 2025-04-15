#ifndef ENGINE_H
#define ENGINE_H

#include "grid.h"
#include "cell.h"

void engine_init();
void engine_exit();
void engine_sleep(int seconds);
Grid engine_create_new_grid();
void engine_free_grid(Grid grid);
void engine_print_grid(Grid grid);


#endif //ENGINE_H