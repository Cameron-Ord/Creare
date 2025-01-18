#include "../inc/font.h"
#include "../inc/render.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>

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
  const int rows = win->height / tile_size.h,
            columns = win->width / tile_size.w;

  fprintf(stdout, "ROWS: %d COLS: %d TILE_WIDTH: %d TILE_HEIGHT: %d\n", rows,
          columns, tile_size.w, tile_size.h);

  Grid grid = {
      rows,
      columns,
  };

  Coordinates coords = {win->width, win->height, grid};
  rend.coord = coords;
}

RendererData *get_renderer(void) { return &rend; }
