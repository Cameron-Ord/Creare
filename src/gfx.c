#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "../inc/gfx.h"
#include "../inc/render.h"

Sprite create_sprite(const char *fn, RendererData *rend) {
  Sprite spr = {0};

  spr.surface = IMG_Load(fn);
  if (!spr.surface) {
    fprintf(stderr, "Failed to create image surface! Error: %s\n",
            IMG_GetError());
    return spr;
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
  spr.texture = SDL_CreateTextureFromSurface(rend->r, spr.surface);
  if (!spr.texture) {
    SDL_FreeSurface(spr.surface);
    fprintf(stderr, "Failed to create image texture! Error: %s\n",
            IMG_GetError());
    return spr;
  }

  spr.width = spr.surface->w;
  spr.height = spr.surface->h;
  spr.valid = 1;

  SDL_FreeSurface(spr.surface);

  return spr;
}
