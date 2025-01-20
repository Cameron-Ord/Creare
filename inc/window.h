#ifndef WINDOW_H
#define WINDOW_H

struct SDL_Window;
typedef struct SDL_Window SDL_Window;

typedef struct WindowData
{
    SDL_Window *w;
    int width, height;
} WindowData;

WindowData *get_window(void);
int create_win(const int w, const int h);
#endif
