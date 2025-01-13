#include "../inc/render.h"
#include "../inc/gfx.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>

static SDL_Rect create_viewport(const int w, const int h);

void render_clear(RendererData *rend) { SDL_RenderClear(rend->r); }

void render_base_bg(RendererData *rend) {
  SDL_SetRenderDrawColor(rend->r, 27, 29, 30, 255);
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

void render_new_option(RendererData *rend, Sprite *spr) {
  const int characters = 3;
  const int tileset_width = sheet_tile_width * characters;

  Coordinates c = rend->coord;
  Grid g = c.grid;

  int t_width = g.tile_width / 2, t_height = g.tile_height / 2;
  int rows = g.rows * 2, columns = g.columns * 2;

  SDL_Rect src[characters];
  SDL_Rect dst[characters];

  SDL_Rect *srcptr = &src[0];
  SDL_Rect *dstptr = &dst[0];

  for (int j = 0, k = 2; j < tileset_width && k < columns;
       j += sheet_tile_width, k++) {
    (*srcptr).x = j, (*srcptr).y = 0, (*srcptr).w = sheet_tile_width,
    (*srcptr).h = sheet_tile_height;

    // Plot rect onto the grid
    const int plotx = (k * t_width);
    const int ploty = ((3 * 2) * t_height);

    (*dstptr).x = plotx, (*dstptr).y = ploty, (*dstptr).w = t_width,
    (*dstptr).h = t_height;

    SDL_RenderCopy(rend->r, spr->texture, srcptr, dstptr);

    srcptr++;
    dstptr++;
  }
}

void render_load_option(RendererData *rend, Sprite *spr) {
  const int characters = 4;
  const int tileset_width = sheet_tile_width * characters;

  Coordinates c = rend->coord;
  Grid g = c.grid;

  int t_width = g.tile_width / 2, t_height = g.tile_height / 2;
  int rows = g.rows * 2, columns = g.columns * 2;

  SDL_Rect src[characters];
  SDL_Rect dst[characters];

  SDL_Rect *srcptr = &src[0];
  SDL_Rect *dstptr = &dst[0];

  for (int j = 0, k = 2; j < tileset_width && k < columns;
       j += sheet_tile_width, k++) {
    (*srcptr).x = j, (*srcptr).y = sheet_tile_height,
    (*srcptr).w = sheet_tile_width, (*srcptr).h = sheet_tile_height;

    // Plot rect onto the grid
    const int plotx = (k * t_width);
    const int ploty = ((3 * 3) * t_height);

    (*dstptr).x = plotx, (*dstptr).y = ploty, (*dstptr).w = t_width,
    (*dstptr).h = t_height;

    SDL_RenderCopy(rend->r, spr->texture, srcptr, dstptr);

    srcptr++;
    dstptr++;
  }
}

void render_logo(RendererData *rend, Sprite *spr) {
  const int characters = 4;
  const int tileset_width = sheet_tile_width * characters;

  Coordinates c = rend->coord;
  Grid g = c.grid;

  int t_width = g.tile_width * 2, t_height = g.tile_height * 2;
  int rows = g.rows / 2, columns = g.columns / 2;

  SDL_Rect src[characters];
  SDL_Rect dst[characters];

  SDL_Rect *srcptr = &src[0];
  SDL_Rect *dstptr = &dst[0];

  for (int j = 0, k = 0; j < tileset_width && k < columns;
       j += sheet_tile_width, k++) {
    (*srcptr).x = j, (*srcptr).y = sheet_tile_height * 2,
    (*srcptr).w = sheet_tile_width, (*srcptr).h = sheet_tile_height;

    // Plot rect onto the grid
    const int plotx = (k * t_width);
    const int ploty = 0;

    (*dstptr).x = plotx, (*dstptr).y = ploty, (*dstptr).w = t_width,
    (*dstptr).h = t_height;

    SDL_RenderCopy(rend->r, spr->texture, srcptr, dstptr);

    srcptr++;
    dstptr++;
  }
}
