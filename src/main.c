#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/binary.h"
#include "../inc/font.h"
#include "../inc/gfx.h"
#include "../inc/render.h"
#include "../inc/window.h"

#define MAP_HEIGHT 1200
#define MAP_WIDTH 1800

int map[MAP_HEIGHT][MAP_WIDTH];

// #define DFT_HEIGHT 720
// #define DFT_WIDTH 1280

const char *font_file = "dogicapixel.ttf";
const char *logo_file = "tmlc-logo.png";

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) {
    fprintf(stderr, "Failed to initialize SDL2! Error: %s\n", SDL_GetError());
    return 1;
  }

  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
    fprintf(stderr, "Failed to load SDL2_image! Error: %s\n", IMG_GetError());
    return 1;
  }

  if (TTF_Init() < 0) {
    fprintf(stderr, "Failed to load SDL2_ttf! Error: %s\n", TTF_GetError());
    return 1;
  }

  WindowData win = create_win();
  if (!win.w) {
    SDL_Quit();
    return 1;
  }

  RendererData rend = create_renderer(&win);
  if (!rend.r) {
    SDL_DestroyWindow(win.w);
    SDL_Quit();
    return 1;
  }

  FontData font = create_font(font_file);
  if (!font.font) {
    fprintf(stderr, "Failed to open font! Error: %s\n", TTF_GetError());
    return 1;
  }

  Sprite logo = create_sprite(logo_file, &rend);
  if (!logo.valid) {
    return 1;
  }

  const int tile_h = 36;
  const int tile_w = 64;

  int running = 1;

  const int tpf = (1000.0 / 60);
  uint64_t frame_start;
  int frame_time;

  SDL_EnableScreenSaver();
  SDL_ShowWindow(win.w);
  while (running) {
    frame_start = SDL_GetTicks64();

    render_base_bg(&rend);
    render_clear(&rend);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {

      case SDL_KEYDOWN: {

      } break;

      case SDL_QUIT: {
        running = 0;
      } break;
      }
    }

    render_load_option(&win, &rend, &logo);
    render_new_option(&win, &rend, &logo);
    render_logo(&win, &rend, &logo);

    frame_time = SDL_GetTicks64() - frame_start;
    if (tpf > frame_time) {
      SDL_Delay(tpf - frame_time);
    }

    render_present(&rend);
  }

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return 0;
}

/* These comments are just notes to myself. */

// Tiles are represented by the grid. So by the values overhead the map will
// contain 1200x1800 tiles.

// Keeping things relative this way makes saving map data easy and I dont need
// to use a coordinate system. As well as being able to scale sprites.

// For the purposes of this program I will be defaulting to a 16:9 ratio
// resolution of 1280x720. And a tile size of 32x18 as it fits perfectly in that
// resolution.

// I calculated this by first choosing a relative tile height with a 16:9 ratio.
// 18 is a multiple of 9 (9 * 2). To calculate the width I do (16/9) *  18

// height = 9 * 2
// width = (16/9) * height
// columns = 1280 / width
// rows = 720 / height

// if I wanted to use a 4:3 ratio it would be something like:

// height = 3 * 4
// width = (4/3) * height
// columns = 1024 / width
// rows = 768 / height

// so 32(width)x18(height)

// So with this I can implement varying aspect ratios but for now lets
// default to 16:9
