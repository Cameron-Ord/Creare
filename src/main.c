#include <SDL2/SDL.h>

typedef struct {
  SDL_Window *w;
  SDL_Renderer *r;
  int width, height;
} WinInfo;

typedef struct {
  int quit;
} ProgramBools;

static void render_clear(SDL_Renderer *r);
static void render_base_bg(SDL_Renderer *r);
static void render_present(SDL_Renderer *r);

int main(int argc, char **argv) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) {
    fprintf(stderr, "Failed to initialize SDL2! -> %s\n", SDL_GetError());
    return 1;
  }

  WinInfo win = {.w = NULL, .r = NULL, .width = 800, .height = 600};
  ProgramBools states = {.quit = 0};

  win.w = SDL_CreateWindow("Creare", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, win.width, win.height,
                           SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
  if (!win.w) {
    fprintf(stderr, "Failed to create window! -> %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  win.r = SDL_CreateRenderer(
      win.w, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!win.r) {
    fprintf(stderr, "Failed to create renderer! -> %s\n", SDL_GetError());
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
