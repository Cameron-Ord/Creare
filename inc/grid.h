#ifndef GRID_H
#define GRID_H
#include <SDL2/SDL_rect.h>

typedef struct {
  int real;
  int viewport;
} Vec2i;

typedef struct {
  int width, height;
  Vec2i x, y;
} Coordinates;

#endif // GRID_H
