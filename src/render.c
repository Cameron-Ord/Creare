#include "../inc/render.h"

static SDL_Rect create_viewport(const int w, const int h);

void render_clear(SDL_Renderer *r) { SDL_RenderClear(r); }

void render_base_bg(SDL_Renderer *r) {
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
}

void render_present(SDL_Renderer *r) { SDL_RenderPresent(r); }

void render_grid(SDL_Renderer *r, const int tile_size, Coordinates *c) {
  SDL_Rect viewport = create_viewport(c->width, c->height);
  SDL_RenderSetViewport(r, &viewport);
  const int cell = 2;

  for (int i = 0; i <= c->height; i += c->grid.tile_height) {
    SDL_Rect row = {.x = 0, .y = i - 1, .w = c->width, cell};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &row);
  }

  for (int i = 0; i <= c->width; i += c->grid.tile_width) {
    SDL_Rect column = {.x = i - 1, .y = 0, .w = cell, c->height};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &column);
  }
}

static SDL_Rect create_viewport(const int w, const int h) {
  SDL_Rect vp = {.x = 0, .y = 0, .w = w, .h = h};
  return vp;
}
