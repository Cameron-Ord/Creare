#ifndef WINDOW_H
#define WINDOW_H

struct SDL_Window;
typedef struct SDL_Window SDL_Window;

struct WindowData {
  SDL_Window *w;
  int width, height;
};

typedef struct WindowData WindowData;

WindowData create_win(void);
#endif
