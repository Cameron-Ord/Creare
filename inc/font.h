#ifndef FONT_H
#define FONT_H
#define CHARBUFF_SIZE 256

struct _TTF_Font;
struct SDL_Texture;
struct SDL_Surface;

typedef struct _TTF_Font TTF_Font;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Surface SDL_Surface;

struct FontData {
  TTF_Font *font;
  int font_size;
};

struct TextData {
  int width, height;
  int x, y;
  SDL_Texture *texture;
  SDL_Surface *surface;
  char string[CHARBUFF_SIZE];
  int valid;
};

typedef struct TextData TextData;
typedef struct FontData FontData;

FontData create_font(const char *fn);

#endif
