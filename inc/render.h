#ifndef RENDER_H
#define RENDER_H
#include "grid.h"
#include <SDL2/SDL_render.h>

void render_sprite_sheet(SDL_Renderer *r, SDL_Texture *spr);
void render_clear(SDL_Renderer *r);
void render_base_bg(SDL_Renderer *r);
void render_present(SDL_Renderer *r);
void render_grid(SDL_Renderer *r, const int tile_size, Coordinates *c);

#endif // RENDER_H
