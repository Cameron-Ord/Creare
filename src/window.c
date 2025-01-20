#include "../inc/window.h"
#include "../inc/render.h"
#include <SDL2/SDL.h>
#include <stdio.h>

WindowData win = {0};

int create_win(const int w, const int h)
{
    win.w =
        SDL_CreateWindow("tmlc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         w, h, SDL_WINDOW_HIDDEN);

    if (!win.w) {
        fprintf(stderr, "Failed to create window! Error:\n%s\n",
                SDL_GetError());
        return 0;
    }

    win.width = w, win.height = h;

    return 1;
}

WindowData *get_window(void) { return &win; }
