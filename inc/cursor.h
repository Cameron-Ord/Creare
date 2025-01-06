#ifndef CURSOR_H
#define CURSOR_H
#include <SDL2/SDL_rect.h>

typedef struct {
  SDL_Rect left, right, top, bottom;
  SDL_Color current_mode;
  SDL_Color tile_mode;
  SDL_Color enemy_mode;
  SDL_Color npc_mode;
} Cursor;

#endif // CURSOR_H
