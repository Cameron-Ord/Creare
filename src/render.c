#include "../inc/render.h"
#include "../inc/font.h"
#include "../inc/gfx.h"
#include <SDL2/SDL_render.h>

static SDL_Rect create_viewport(const int w, const int h);

void render_str(const RenderStr *r_str, const Sprite *spr, const Grid *g) {
  const int tile_width = get_tile_size().w;
  const int tile_height = get_tile_size().h;

  SDL_Renderer *r = get_renderer()->r;
  for (size_t i = 0, col = r_str->col;
       i < r_str->len && col < (size_t)g->columns; i++, col++) {
    CharTable p = table_get_char(r_str->str[i]);

    const int x = col * g->tile_w;
    const int y = r_str->row * g->tile_h;

    SDL_Rect src = {p.x, p.y, tile_width, tile_height};
    SDL_Rect dst = {x, y, g->tile_w, g->tile_h};

    SDL_RenderCopy(r, spr->texture, &src, &dst);
  }
}

void render_clear(void) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_RenderClear(r);
}

void render_base_bg(void) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
}

void render_present(void) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_RenderPresent(r);
}

void render_grid(Coordinates *c, const int w, const int h) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_Rect viewport = create_viewport(w, h);
  SDL_RenderSetViewport(r, &viewport);
  const int cell = 2;

  for (int i = 0; i <= h; i += get_tile_size().h) {
    SDL_Rect row = {.x = 0, .y = i - 1, .w = w, cell};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &row);
  }

  for (int i = 0; i <= w; i += get_tile_size().w) {
    SDL_Rect column = {.x = i - 1, .y = 0, .w = cell, h};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &column);
  }
}

static SDL_Rect create_viewport(const int w, const int h) {
  SDL_Rect vp = {.x = 0, .y = 0, .w = w, .h = h};
  return vp;
}
