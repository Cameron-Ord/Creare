#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { N = 110, H = 104, E = 101, PERIOD = 46 } ascii_codes;

typedef struct {
  SDL_Window *w;
  SDL_Renderer *r;
  int width, height;
} WinInfo;

typedef struct {
  int quit;
} ProgramBools;

// This just contains garbage example data for the binary file format, I will
// make this proper later. For now it's like this for the purpose of setting it
// up.
typedef struct {
  int x, j, g, valid;
} crx_spec;

#define DFT_HEIGHT 600
#define DFT_WIDTH 800

static void render_clear(SDL_Renderer *r);
static void render_base_bg(SDL_Renderer *r);
static void render_present(SDL_Renderer *r);
static void show_help(void);
static int get_extension_idx(const char *arg);
static int check_ftype(const int idx, const char *arg);

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

// Once this gets going, I am going to have to have dynamically allocated memory
// inside the crx_spec struct. So multiple sizes values will be stored inside
// the base struct, then I will have to malloc them before use so I will be
// freading a bunch of things seperately. But lets try to keep it simple.
static crx_spec read_file(const char *fn) {
  fprintf(stdout, "Reading : %s\n", fn);
  crx_spec spec = {0};

  FILE *fptr = fopen(fn, "rb");
  if (!fptr) {
    fprintf(stderr, "Failed to open file in read mode! Error:\n%s\n",
            strerror(errno));
    return spec;
  }

  const size_t read = fread(&spec, sizeof(crx_spec), 1, fptr);
  if (read != 1) {
    fprintf(stderr, "Could not read file! Error:\n%s\n", strerror(errno));
    fclose(fptr);
    return spec;
  }

  fclose(fptr);

  spec.valid = 1;
  return spec;
}

static crx_spec create_file(const char *fn) {
  fprintf(stdout, "Creating : %s\n", fn);
  crx_spec spec = {0};

  FILE *fptr = fopen(fn, "wb");
  if (!fptr) {
    fprintf(stderr, "Failed to open file in write mode! Error:\n%s\n",
            strerror(errno));
    return spec;
  }

  const size_t wrtn = fwrite(&spec, sizeof(crx_spec), 1, fptr);
  if (wrtn != 1) {
    fprintf(stderr, "Failed to write to file!\n");
    fclose(fptr);
    return spec;
  }

  fclose(fptr);

  spec.valid = 1;
  return spec;
}

int main(int argc, char **argv) {
  crx_spec spec = {0};

  if (argc > 1) {
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
        if (argc == 3) {
          if (!check_ftype(get_extension_idx(argv[2]), argv[2])) {
            printf("Invalid binary file type!\n");
            return 1;
          } else {
            spec = create_file(argv[2]);
            if (!spec.valid) {
              return 1;
            }
          }
        }

      } break;

      case E: {
        if (argc == 3) {
          if (!check_ftype(get_extension_idx(argv[2]), argv[2])) {
            printf("Invalid binary file type!\n");
            return 1;
          } else {
            spec = read_file(argv[2]);
            if (!spec.valid) {
              return 1;
            }
          }

        } else {
          fprintf(stdout, "Invalid arguments\n");
          return 1;
        }
      } break;
      }
      i++;
    }

  } else {
    fprintf(stdout, "Usage: <prefix> <argument>\nUse the h prefix for help.\n");
    return 0;
  }

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) {
    fprintf(stderr, "Failed to initialize SDL2! Error:\n%s\n", SDL_GetError());
    return 1;
  }

  if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
    fprintf(stderr, "Failed to load SDL2_image! Error:\n%s\n", SDL_GetError());
    return 1;
  }

  // Will need this later, but for now its not used
  const char *home = getenv("HOME");
  if (!home) {
    fprintf(stderr, "getenv() failed! Error:\n%s\n", strerror(errno));
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
      case SDL_KEYDOWN: {

      } break;

      case SDL_QUIT: {
        states.quit = 1;
      } break;
      }
    }

    frame_time = SDL_GetTicks64() - frame_start;
    if (tpf > frame_time) {
      SDL_Delay(tpf - frame_time);
    }

    render_present(win.r);
  }

  return 0;
}

static void render_clear(SDL_Renderer *r) { SDL_RenderClear(r); }

static void render_base_bg(SDL_Renderer *r) {
  SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
}

static void render_present(SDL_Renderer *r) { SDL_RenderPresent(r); }
static void show_help(void) { fprintf(stdout, "Not implemented\n"); }
static int get_extension_idx(const char *arg) {
  int i = 0;
  while (arg[i] != '\0') {
    if (arg[i] == PERIOD) {
      return i;
    }
    i++;
  }
  return -1;
}

static int check_ftype(const int idx, const char *arg) {
  if (idx < 0) {
    printf("Could not find delimiter\n");
    return 0;
  }

  const size_t len = strlen(arg) + 1;
  char buffer[len];
  int i = idx;
  int j = 0;

  while (arg[i] != '\0') {
    buffer[j] = arg[i];
    i++;
    j++;
  }

  buffer[j] = '\0';
  if (strcmp(buffer, "crx")) {
    return 1;
  }

  return 0;
}
