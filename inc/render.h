#ifndef RENDER_H
#define RENDER_H
#include <stddef.h>
// Defined elsewhere in other headers. Just forward declare and include headers
// in source files.
struct WindowData;
struct SDL_Renderer;
struct Sprite;

typedef struct Sprite Sprite;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct WindowData WindowData;

struct TileDm {
  int w, h;
};

typedef struct TileDm TileDm;

typedef struct {
  int rows, columns;
} Grid;

struct Coordinates {
  int width, height;
  Grid grid;
};

typedef struct Coordinates Coordinates;

struct RendererData {
  SDL_Renderer *r;
  Coordinates coord;
};

typedef struct RendererData RendererData;
TileDm get_tile_size(void);
void render_str(const int row, const int col, const char *str, const size_t len,
                const Sprite *spr);
void set_window_vga(const WindowData *win);
int create_renderer(WindowData *win);
RendererData *get_renderer(void);
void render_clear(void);
void render_base_bg(void);
void render_present(void);
void render_grid(Coordinates *c);
void render_char(const int x, const int y, const char c, const Sprite *spr);

#endif // RENDER_H
