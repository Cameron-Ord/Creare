#include "../inc/render.h"
#include "../inc/font.h"
#include "../inc/gfx.h"
#include <SDL2/SDL_render.h>

static SDL_Rect create_viewport(const int w, const int h);

void render_str(const int row, const int col, const char *str, const size_t len,
                const Sprite *spr) {
  const int tile_width = get_tile_size().w;
  const int tile_height = get_tile_size().h;

  int col_pos = col;

  SDL_Renderer *r = get_renderer()->r;
  for (size_t i = 0; i < len; i++) {
    CharTable p = table_get_char(str[i]);

    const int x = col_pos * tile_width;
    const int y = row * tile_height;

    SDL_Rect src = {p.x, p.y, tile_width, tile_height};
    SDL_FRect dst = {x, y, tile_width, tile_height};

    col_pos++;
    SDL_RenderCopyF(r, spr->texture, &src, &dst);
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

void render_grid(Coordinates *c) {
  SDL_Renderer *r = get_renderer()->r;
  SDL_Rect viewport = create_viewport(c->width, c->height);
  SDL_RenderSetViewport(r, &viewport);
  const int cell = 2;

  for (int i = 0; i <= c->height; i += get_tile_size().h) {
    SDL_Rect row = {.x = 0, .y = i - 1, .w = c->width, cell};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &row);
  }

  for (int i = 0; i <= c->width; i += get_tile_size().w) {
    SDL_Rect column = {.x = i - 1, .y = 0, .w = cell, c->height};
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &column);
  }
}

static SDL_Rect create_viewport(const int w, const int h) {
  SDL_Rect vp = {.x = 0, .y = 0, .w = w, .h = h};
  return vp;
}
