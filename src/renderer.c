#include "../inc/render.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>

RendererData create_renderer(WindowData *win) {
  RendererData rend = {0};

  rend.r = SDL_CreateRenderer(
      win->w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!rend.r) {
    fprintf(stderr, "Failed to create renderer! Error: %s\n", SDL_GetError());
    return rend;
  }

  return rend;
}

Coordinates set_window_vga(const WindowData *win) {
  const int rows = 6, columns = 8;
  const int tile_width = win->width / columns;
  const int tile_height = win->height / rows;

  fprintf(stdout, "ROWS: %d COLS: %d TILE_WIDTH: %d TILE_HEIGHT: %d\n", rows,
          columns, tile_width, tile_height);

  Grid grid = {.rows = rows,
               .columns = columns,
               .tile_width = tile_width,
               .tile_height = tile_height};

  Coordinates coords = {
      .width = win->width, .height = win->height, .grid = grid};

  return coords;
}
