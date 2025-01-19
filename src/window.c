#include "../inc/window.h"
#include "../inc/render.h"
#include <SDL2/SDL.h>
#include <stdio.h>
// By default the program opens in 4:3 Standard Definition.
// When building maps, the option for SD or HD will be present.
// I drew my font characters in 4:3 but i'll figure that out later.

#define DFT_HEIGHT 240
#define DFT_WIDTH 320

WindowData win = {.w = NULL, .width = DFT_WIDTH, .height = DFT_HEIGHT};

int create_win(void)
{
    win.w =
        SDL_CreateWindow("tmlc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         DFT_WIDTH, DFT_HEIGHT, SDL_WINDOW_HIDDEN);

    if (!win.w) {
        fprintf(stderr, "Failed to create window! Error:\n%s\n",
                SDL_GetError());
        return 0;
    }

    return 1;
}

WindowData *get_window(void) { return &win; }
