#include "../inc/font.h"
#include "../inc/render.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RendererData rend = {0};
Vec2i grid[3] = {{32, 18}, {0}, {0}};

Vec2i *get_grid(void) { return grid; }

void grid_update_window(const int w, const int h)
{
    grid[1].w = w, grid[1].h = h;
}

void grid_update_sprite_size(const int w, const int h)
{
    grid[2].w = w / grid->w, grid[2].h = h / grid->h;
}

int create_renderer(WindowData *win)
{
    rend.r = SDL_CreateRenderer(
        win->w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!rend.r) {
        fprintf(stderr, "Failed to create renderer! Error: %s\n",
                SDL_GetError());
        return 0;
    }

    return 1;
}

RendererData *get_renderer(void) { return &rend; }
