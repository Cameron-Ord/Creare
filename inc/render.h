#ifndef RENDER_H
#define RENDER_H
#include "vectors.h"
#include <stddef.h>
// Defined elsewhere in other headers. Just forward declare and include headers
// in source files.
struct WindowData;
struct SDL_Renderer;
struct Sprite;

typedef struct Sprite Sprite;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct WindowData WindowData;

struct RenderStr
{
    int row, col;
    char *str;
    size_t len;
};

typedef struct RenderStr RenderStr;

struct RendererData
{
    SDL_Renderer *r;
};

typedef struct RendererData RendererData;

Vec4i *get_sd_grids(void);
Vec4i *get_hd_grids(void);
Vec2i *get_sd_tile_sizes(void);
Vec2i *get_hd_tile_sizes(void);
void set_window_sd(const WindowData *win);
void set_window_hd(const WindowData *win);
int create_renderer(WindowData *win);
RendererData *get_renderer(void);
void render_clear(void);
void render_base_bg(void);
void render_present(void);
void render_grid(Vec4i *g, const int w, const int h);
void render_str(Vec4i pos, const Vec4i *g, const Sprite *s, const char *str, const int len);
#endif // RENDER_H
