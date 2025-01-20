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

typedef struct RenderStr
{
    Vec2i locn;
    char *str;
    size_t len;
    Vec2i char_grid_space;
    Vec2i *grid;
    int offset;
} RenderStr;

typedef struct RendererData
{
    SDL_Renderer *r;
} RendererData;

void grid_update_sprite_size(const int w, const int h);
Vec2i *get_grid(void);
void grid_update_window(const int w, const int h);
int create_renderer(WindowData *win);
RendererData *get_renderer(void);
void render_clear(void);
void render_base_bg(void);
void render_present(void);
void render_grid(Vec2i *g);
void render_str(const RenderStr *str, const Sprite *spr);
#endif // RENDER_H
