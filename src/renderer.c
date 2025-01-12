#include "../inc/render.h"
#include "../inc/window.h"
#include <SDL2/SDL_render.h>

RendererData create_renderer(WindowData *win) {
  RendererData rend;

  rend.r = SDL_CreateRenderer(
      win->w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!rend.r) {
    fprintf(stderr, "Failed to create renderer! Error: %s\n", SDL_GetError());
    return rend;
  }

  return rend;
}
