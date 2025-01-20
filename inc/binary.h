#ifndef BINARY_H
#define BINARY_H

typedef struct Tile
{
    char type[256];
    int src_x, src_y;
    int width, height;
} Tile;

typedef struct CrxSpec
{
    Tile **map;
    int map_rows, map_cols;
    char spritesheet_path[256];
    int valid;
} CrxSpec;

int set_home_env(void);
CrxSpec create_file(const char *fn);
CrxSpec read_file(const char *fn);
int get_extension_idx(const char *arg);
int check_ftype(const int idx, const char *arg);
#endif // BINARY_H
