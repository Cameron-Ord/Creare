#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/binary.h"
#include "../inc/grid.h"
#include "../inc/render.h"

typedef struct {
  SDL_Window *w;
  SDL_Renderer *r;
  int width, height;
} WinInfo;

typedef struct {
  int quit;
} ProgramBools;

const int tile_size = 32;

#define DFT_HEIGHT 600
#define DFT_WIDTH 800

static void show_help(void);
static void update_coordinates(Coordinates *c, const int w, const int h);

static SDL_Window *create_win(void) {
  SDL_Window *w = SDL_CreateWindow(
      "Creare", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DFT_WIDTH,
      DFT_HEIGHT, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);

  if (!w) {
    fprintf(stderr, "Failed to create window! Error:\n%s\n", SDL_GetError());
    return NULL;
  }

  return w;
}

static SDL_Renderer *create_renderer(SDL_Window *w) {
  SDL_Renderer *r = SDL_CreateRenderer(
      w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if (!r) {
    fprintf(stderr, "Failed to create renderer! Error\n%s\n", SDL_GetError());
    return NULL;
  }

  return r;
}

int main(int argc, char **argv) {
  crx_spec spec = {0};

  if (argc > 1 && argc < 5) {
    int i = 0;
    while (argv[1][i] != '\0') {
      switch (argv[1][i]) {
      default: {
        fprintf(stdout, "Invalid prefix\n");
        return 1;
      } break;

      case H: {
        show_help();
        return 0;
      } break;

      case N: {
        if (argc == 4) {
          if (!check_ftype(get_extension_idx(argv[2]), argv[2])) {
            fprintf(stderr, "Must use the .crx file extension convention!\n");
            return 1;
          } else {
            spec = create_file(argv[2]);
            if (!spec.valid) {
              fprintf(stderr, "File writing failed! -> EXIT\n");
              return 1;
            }
          }
        }

      } break;

      case E: {
        if (argc == 4) {
          if (!check_ftype(get_extension_idx(argv[2]), argv[2])) {
            fprintf(
                stderr,
                "WARN - Binary does not have the expected file extension!\n");
          }
          spec = read_file(argv[2]);
          if (!spec.valid) {
            fprintf(stderr, "File read failed! -> EXIT\n");
            return 1;
          }

        } else {
          fprintf(stderr, "Invalid arguments\n");
          return 1;
        }
      } break;
      }
      i++;
    }

  } else {
    fprintf(stdout, "Usage: <prefix> <file> <path to spritesheet>\nUse the h "
                    "prefix for help.\n");
    return 0;
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) {
    fprintf(stderr, "Failed to initialize SDL2! Error: %s\n", SDL_GetError());
    return 1;
  }

  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
    fprintf(stderr, "Failed to load SDL2_image! Error: %s\n", SDL_GetError());
    return 1;
  }

  WinInfo win = {.w = NULL, .r = NULL, .width = 800, .height = 600};
  ProgramBools states = {.quit = 0};

  win.w = create_win();
  if (!win.w) {
    SDL_Quit();
    return 1;
  }

  win.r = create_renderer(win.w);
  if (!win.r) {
    SDL_DestroyWindow(win.w);
    SDL_Quit();
    return 1;
  }

  SDL_Surface *spr_surface = IMG_Load(argv[3]);
  if (!spr_surface) {
    fprintf(stderr, "Failed to load spritesheet! Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(win.w);
    SDL_Quit();
    return 1;
  }

  SDL_Texture *spr_texture = SDL_CreateTextureFromSurface(win.r, spr_surface);
  if (!spr_texture) {
    fprintf(stderr, "Failed to load spritesheet! Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(win.w);
    SDL_Quit();
    return 1;
  }

  Coordinates coordinates = {
      .width = win.width,
      .height = win.height,
      .x = {0},
      .y = {0},
  };

  const int tpf = (1000.0 / 60);
  uint64_t frame_start;
  int frame_time;

  SDL_EnableScreenSaver();
  SDL_ShowWindow(win.w);
  while (!states.quit) {
    frame_start = SDL_GetTicks64();

    render_base_bg(win.r);
    render_clear(win.r);

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      switch (e.type) {

      case SDL_WINDOWEVENT: {
        switch (e.window.event) {
        default:
          break;

        case SDL_WINDOWEVENT_RESIZED: {
          SDL_GetWindowSize(win.w, &win.width, &win.height);
          update_coordinates(&coordinates, win.width, win.height);
        } break;

        case SDL_WINDOWEVENT_SIZE_CHANGED: {
          SDL_GetWindowSize(win.w, &win.width, &win.height);
          update_coordinates(&coordinates, win.width, win.height);
        } break;
        }
      } break;

      case SDL_KEYDOWN: {

      } break;

      case SDL_QUIT: {
        states.quit = 1;
      } break;
      }
    }

    render_grid(win.r, tile_size, &coordinates);

    frame_time = SDL_GetTicks64() - frame_start;
    if (tpf > frame_time) {
      SDL_Delay(tpf - frame_time);
    }

    render_present(win.r);
  }

  return 0;
}

static void show_help(void) { fprintf(stdout, "Not implemented\n"); }

static void update_coordinates(Coordinates *c, const int w, const int h) {
  c->width = w;
  c->height = h;
}
