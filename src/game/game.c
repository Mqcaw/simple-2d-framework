#include <stdio.h>
#include <stdlib.h>
#include "engine.h"
#include "game.h"
#include "cell.h"
#include "grid.h"

int g_running = 0;
Grid g_grid;

void game_init() {
    printf("Game starting\n");
    engine_init();
    g_running = 1;
    g_grid = engine_create_new_grid();
    printf("Game started\n");
    game_run();
}

void game_run() {
    printf("Game running\n\n");
    while (g_running) {
        //poll events
        
        //tick
        //render

        //present
        printf("%i\n", g_grid.array[1][1].x);

        printf("Grid size: %zu\n", sizeof(g_grid));
        printf("Cell size: %zu\n", sizeof(g_grid.array[1][1]));

        engine_sleep(2);
        //engine_print_grid(g_grid);
        

        game_stop();

    }
    game_exit();
}

void game_exit() {
    printf("Exiting game\n");
    engine_exit();
    printf("Game exited\n");
}

void game_stop() {
    printf("Game stopping\n");
    g_running = 0;
    engine_free_grid(g_grid);
    printf("Game stopped\n");
}