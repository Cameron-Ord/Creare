#include "../inc/window.h"
#include "../inc/render.h"
#include <SDL2/SDL.h>

#define DFT_HEIGHT 240
#define DFT_WIDTH 320

WindowData win = {.w = NULL, .width = DFT_WIDTH, .height = DFT_HEIGHT};

int create_win(void) {
  win.w =
      SDL_CreateWindow("tmlc", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       DFT_WIDTH, DFT_HEIGHT, SDL_WINDOW_HIDDEN);

  if (!win.w) {
    fprintf(stderr, "Failed to create window! Error:\n%s\n", SDL_GetError());
    return 0;
  }

  return 1;
}

WindowData *get_window(void) { return &win; }
