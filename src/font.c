#include "../inc/font.h"
#include <SDL2/SDL_ttf.h>

static TTF_Font *open_font(const char *fn, const int fsize) {
  return TTF_OpenFont(fn, fsize);
}

FontData create_font(const char *fn) {
  FontData font = {.font = NULL, .font_size = 16};
  font.font = open_font(fn, font.font_size);
  return font;
}
