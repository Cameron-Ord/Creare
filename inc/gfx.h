#ifndef GFX_H
#define GFX_H
#define TYPE_STR_SIZE 64

struct SDL_Texture;
typedef struct SDL_Texture SDL_Texture;

struct SDL_Surface;
typedef struct SDL_Surface SDL_Surface;

struct RendererData;
typedef struct RendererData RendererData;

typedef struct Sprite
{
    int valid;
    SDL_Texture *texture;
    SDL_Surface *surface;
    int x, y;
    int width, height;
    char type[TYPE_STR_SIZE];
} Sprite;

Sprite create_sprite(const char *fn, RendererData *rend);

#endif
