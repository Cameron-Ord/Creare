#ifndef GRID_H
#define GRID_H
#include <SDL2/SDL_rect.h>

typedef struct {
  int real;
  int viewport;
} Vec2i;

typedef struct {
  int rows, columns;
  int tile_width, tile_height;
} Grid;

typedef struct {
  int width, height;
  Vec2i x, y;
  Grid grid;
} Coordinates;

#endif // GRID_H
