#include "../inc/font.h"
#include "../inc/render.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

RendererData rend = {0};

TileDm sd_tile_sizes[] = {{16, 16}, {32, 32}, {64, 64}};
TileDm hd_tile_sizes[] = {{32, 18}, {64, 36}};

Grid hd_grids[2];
Grid sd_grids[3];

TileDm *get_sd_tile_sizes(void) { return sd_tile_sizes; }
TileDm *get_hd_tile_sizes(void) { return hd_tile_sizes; }

Grid *get_hd_grids(void) { return hd_grids; }
Grid *get_sd_grids(void) { return sd_grids; }

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

void set_window_sd(const WindowData *win)
{
    const int w = win->width;
    const int h = win->height;

    const int w16 = sd_tile_sizes[0].w;
    const int h16 = sd_tile_sizes[0].h;

    const int w32 = sd_tile_sizes[1].w;
    const int h32 = sd_tile_sizes[1].h;

    const int w64 = sd_tile_sizes[2].w;
    const int h64 = sd_tile_sizes[2].h;

    const int cols_16 = w / w16;
    const int rows_16 = h / h16;

    const int cols_32 = w / w32;
    const int rows_32 = h / h32;

    const int cols_64 = w / w32;
    const int rows_64 = h / h32;

    Grid g[] = {{rows_16, cols_16, w16, h16},
                {rows_32, cols_32, w32, h32},
                {rows_64, cols_64, w64, h64}};
    memcpy(sd_grids, g, sizeof(g));
}

void set_window_hd(const WindowData *win)
{
    const int w = win->width;
    const int h = win->height;

    const int w32 = hd_tile_sizes[0].w;
    const int h18 = hd_tile_sizes[0].h;

    const int w64 = hd_tile_sizes[1].w;
    const int h36 = hd_tile_sizes[1].h;

    const int cols_16 = w / w32;
    const int rows_16 = h / h18;

    const int cols_32 = w / w64;
    const int rows_32 = h / h36;

    Grid g[] = {{rows_16, cols_16, w32, h18}, {rows_32, cols_32, w64, h36}};
    memcpy(hd_grids, g, sizeof(g));
}

RendererData *get_renderer(void) { return &rend; }
