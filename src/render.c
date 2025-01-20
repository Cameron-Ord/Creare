#include "../inc/render.h"
#include "../inc/font.h"
#include "../inc/gfx.h"
#include <SDL2/SDL_render.h>
#include <stdio.h>

static SDL_Rect create_viewport(const int w, const int h);

void render_clear(void)
{
    SDL_Renderer *r = get_renderer()->r;
    SDL_RenderClear(r);
}

void render_base_bg(void)
{
    SDL_Renderer *r = get_renderer()->r;
    SDL_SetRenderDrawColor(r, 39, 40, 32, 255);
}

void render_present(void)
{
    SDL_Renderer *r = get_renderer()->r;
    SDL_RenderPresent(r);
}

void render_str(const RenderStr *str, const Sprite *spr)
{
    SDL_Renderer *r = get_renderer()->r;
    Vec2i src_size = get_font_sizing();
    for (size_t i = 0, j = str->locn.w; i < str->len; i++, j++) {
        const char c = str->str[i];
        if (not_known(c) || c == 32) {
            continue;
        }

        Vec2i locn = get_char_locn(c);
        SDL_Rect src = {locn.w, locn.h + str->offset, src_size.w, src_size.h};

        const int grid_w = str->char_grid_space.w * str->grid[2].w;
        const int grid_h = str->char_grid_space.h * str->grid[2].h;

        const int plotx = j * grid_w;
        const int ploty = str->locn.h * grid_h;

        SDL_Rect dst = {plotx, ploty, grid_w, grid_h};
        SDL_RenderCopy(r, spr->texture, &src, &dst);
    }
}

void render_grid(Vec2i *g)
{
    SDL_Renderer *r = get_renderer()->r;
    const int cell = 2;
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);

    for (int i = 0; i <= g[1].h; i += g[2].h) {
        SDL_Rect row = {.x = 0, .y = i - 1, .w = g[1].w, cell};
        SDL_SetRenderDrawColor(r, 174, 129, 255, 50);
        SDL_RenderFillRect(r, &row);
    }

    for (int i = 0; i <= g[1].w; i += g[2].w) {
        SDL_Rect column = {.x = i - 1, .y = 0, .w = cell, g[1].h};
        SDL_SetRenderDrawColor(r, 174, 129, 255, 50);
        SDL_RenderFillRect(r, &column);
    }
}

static SDL_Rect create_viewport(const int w, const int h)
{
    SDL_Rect vp = {.x = 0, .y = 0, .w = w, .h = h};
    return vp;
}
