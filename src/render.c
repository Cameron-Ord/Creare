#include "../inc/render.h"
#include "../inc/font.h"
#include "../inc/gfx.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>


static SDL_Rect create_viewport(const int w, const int h);

void render_clear(void) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_RenderClear(r);
}

void render_base_bg(void) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
}

void render_present(void) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_RenderPresent(r);
}

void render_grid(Grid *g, const int w, const int h) {
  SDL_Renderer *r = get_renderer()->r;
  const int cell = 2;

  for (int i = 0; i <= h; i += g->tile_h) {
    SDL_Rect row = {.x = 0, .y = i - 1, .w = w, cell};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &row);
  }

  for (int i = 0; i <= w; i += g->tile_w) {
    SDL_Rect column = {.x = i - 1, .y = 0, .w = cell, h};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &column);
  }
}

static SDL_Rect create_viewport(const int w, const int h) {
  SDL_Rect vp = {.x = 0, .y = 0, .w = w, .h = h};
  return vp;
}
