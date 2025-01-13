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
  int rows, columns;
  int tile_width, tile_height;
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

Coordinates set_window_vga(const WindowData *win);
RendererData create_renderer(WindowData *win);
void render_logo(RendererData *rend, Sprite *spr);
void render_load_option(RendererData *rend, Sprite *spr);
void render_new_option(RendererData *rend, Sprite *spr);
void render_clear(RendererData *rend);
void render_base_bg(RendererData *rend);
void render_present(RendererData *rend);
void render_grid(RendererData *rend, Coordinates *c);

#endif // RENDER_H
