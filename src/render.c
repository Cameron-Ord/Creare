#include "../inc/render.h"
#include "../inc/gfx.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>

static SDL_Rect create_viewport(const int w, const int h);

void render_clear(RendererData *rend) { SDL_RenderClear(rend->r); }

void render_base_bg(RendererData *rend) {
  SDL_SetRenderDrawColor(rend->r, 248, 248, 242, 255);
}

void render_present(RendererData *rend) { SDL_RenderPresent(rend->r); }

void render_grid(RendererData *rend, Coordinates *c) {
  SDL_Rect viewport = create_viewport(c->width, c->height);
  SDL_RenderSetViewport(rend->r, &viewport);
  const int cell = 2;

  for (int i = 0; i <= c->height; i += c->grid.tile_height) {
    SDL_Rect row = {.x = 0, .y = i - 1, .w = c->width, cell};
    SDL_SetRenderDrawColor(rend->r, 255, 255, 255, 255);
    SDL_RenderFillRect(rend->r, &row);
  }

  for (int i = 0; i <= c->width; i += c->grid.tile_width) {
    SDL_Rect column = {.x = i - 1, .y = 0, .w = cell, c->height};
    SDL_SetRenderDrawColor(rend->r, 255, 255, 255, 255);
    SDL_RenderFillRect(rend->r, &column);
  }
}

static SDL_Rect create_viewport(const int w, const int h) {
  SDL_Rect vp = {.x = 0, .y = 0, .w = w, .h = h};
  return vp;
}

const int sheet_tile_width = 32;
const int sheet_tile_height = 32;

void render_new_option(WindowData *win, RendererData *rend, Sprite *spr) {}

void render_load_option(WindowData *win, RendererData *rend, Sprite *spr) {}

void render_logo(WindowData *win, RendererData *rend, Sprite *spr) {
  const int characters = 4;
  const int tile_height = 64;
  const int tile_width = 64;

  const int columns = win->width / tile_width;
  const int rows = win->height / tile_height;

  SDL_Rect src[characters];
  SDL_Rect dst[characters];

  SDL_Rect *srcptr = &src[0];
  SDL_Rect *dstptr = &dst[0];

  const int total_width = sheet_tile_width * characters;
  int current_column = 1;

  for (int i = 0; i < total_width; i += sheet_tile_width) {
    (*srcptr).x = i, (*srcptr).y = sheet_tile_height * 2,
    (*srcptr).w = sheet_tile_width, (*srcptr).h = sheet_tile_height;

    const int x = (current_column * tile_width) - (tile_width * 0.5);
    const int y = (1 * tile_width) - (tile_height * 0.5);

    (*dstptr).x = x, (*dstptr).y = y, (*dstptr).w = tile_width,
    (*dstptr).h = tile_height;

    SDL_RenderCopy(rend->r, spr->texture, srcptr, dstptr);

    current_column += 2;
    srcptr++;
    dstptr++;
  }
}
