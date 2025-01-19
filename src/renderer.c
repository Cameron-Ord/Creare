#include "../inc/font.h"
#include "../inc/render.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

RendererData rend = {0};
TileDm tile_size = {16, 16};
TileDm get_tile_size(void) { return tile_size; }

int create_renderer(WindowData *win) {
  rend.r = SDL_CreateRenderer(
      win->w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!rend.r) {
    fprintf(stderr, "Failed to create renderer! Error: %s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

void set_window_vga(const WindowData *win) {
  const int rows_norm = win->height / tile_size.h,
            columns_norm = win->width / tile_size.w;

  const int rows_small = win->height / (tile_size.h / 2),
            columns_small = win->width / (tile_size.w / 2);

  const int rows_big = win->height / (tile_size.h * 2),
            columns_big = win->width / (tile_size.w * 2);

  Grid grid_norm = {rows_norm, columns_norm, tile_size.w, tile_size.h};
  Grid grid_small = {rows_small, columns_small, tile_size.w / 2,
                     tile_size.h / 2};
  Grid grid_big = {rows_big, columns_big, tile_size.w * 2, tile_size.h * 2};

  Coordinates coords = {grid_big, grid_small, grid_norm};
  rend.coord = coords;
}

Coordinates *get_render_grids(void) { return &rend.coord; }
RendererData *get_renderer(void) { return &rend; }
