#ifndef RENDER_H
#define RENDER_H

// Defined elsewhere in other headers. Just forward declare and include headers
// in source files.
struct WindowData;
struct SDL_Renderer;
struct Sprite;

typedef struct Sprite Sprite;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct WindowData WindowData;

typedef struct {
  int real;
  int viewport;
} Vec2i;

typedef struct {
  int rows, columns;
  int tile_width, tile_height;
} Grid;

struct Coordinates {
  int width, height;
  Vec2i x, y;
  Grid grid;
};

struct RendererData {
  SDL_Renderer *r;
};

typedef struct Coordinates Coordinates;
typedef struct RendererData RendererData;

RendererData create_renderer(WindowData *win);

void render_new_option(WindowData *win, RendererData *rend, Sprite *spr);
void render_load_option(WindowData *win, RendererData *rend, Sprite *spr);
void render_logo(WindowData *win, RendererData *rend, Sprite *spr);
void render_clear(RendererData *rend);
void render_base_bg(RendererData *rend);
void render_present(RendererData *rend);
void render_grid(RendererData *rend, Coordinates *c);

#endif // RENDER_H
