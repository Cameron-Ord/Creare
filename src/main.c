#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>

#include "../inc/font.h"
#include "../inc/gfx.h"
#include "../inc/render.h"
#include "../inc/window.h"

#define MAP_HEIGHT 1200
#define MAP_WIDTH 1800
typedef enum
{
    MENU = 0,
    CREATOR = 1
} Modes;

const char *strings[] = {"NEW", "LOAD"};
const int sizes[] = {3, 4};

int menu_cursor = 0;
const int selection_offset[] = {0, 16 * 5};

const int modes[] = {MENU, CREATOR};
int current_mode = MENU;

int map[MAP_HEIGHT][MAP_WIDTH];

// #define DFT_HEIGHT 720
// #define DFT_WIDTH 1280

const char *charsheet_fn = "chars.png";

static void paint_menu(const char **strings, const int *sizes, const Grid *g, const Sprite *s);

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "Failed to initialize SDL2! Error: %s\n",
                SDL_GetError());
        return 1;
    }

    if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
        fprintf(stderr, "Failed to load SDL2_image! Error: %s\n",
                IMG_GetError());
        return 1;
    }

    if (!create_win()) {
        SDL_Quit();
        return 1;
    }

    if (!create_renderer(get_window())) {
        SDL_DestroyWindow(get_window()->w);
        SDL_Quit();
        return 1;
    }

    set_window_sd(get_window());
    set_window_hd(get_window());

    Grid current_grid = get_sd_grids()[1];

    Sprite char_sheet = create_sprite(charsheet_fn, get_renderer());
    if (!char_sheet.valid) {
        return 1;
    }

    char_set_table();
    int running = 1;

    const int tpf = (1000.0 / 30);
    uint64_t frame_start;
    int frame_time;

    SDL_EnableScreenSaver();
    SDL_ShowWindow(get_window()->w);
    while (running) {
        frame_start = SDL_GetTicks64();

        render_base_bg();
        render_clear();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            default:
                break;

            case SDL_KEYDOWN:
            {
                const uint32_t keycode = e.key.keysym.sym;
                const uint16_t keymod = e.key.keysym.mod;

                switch (current_mode) {
                default:
                    break;

                case MENU:
                {
                    switch (keycode) {
                    default:
                        break;
                    case SDLK_RETURN:
                    {
                        // Set to creator mode, create a new crx file or load one. Then make resolution change to window and present grid.
                    } break;

                    case SDLK_UP:
                    {
                        menu_cursor = !menu_cursor;
                    } break;

                    case SDLK_DOWN:
                    {
                        menu_cursor = !menu_cursor;
                    } break;
                    }
                } break;

                case CREATOR:
                {
                    switch (keycode) {
                    default:
                        break;
                    }
                } break;
                }
            } break;

            case SDL_QUIT:
            {
                running = 0;
            } break;
            }
        }

        paint_menu(strings, sizes, &current_grid, &char_sheet);

        frame_time = SDL_GetTicks64() - frame_start;
        if (tpf > frame_time) {
            SDL_Delay(tpf - frame_time);
        }

        render_present();
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}

static void paint_menu(const char **strings, const int *sizes, const Grid *g, const Sprite *s)
{
    Vec4i new_prompt = {.x = 3, .y = 3, .offset_x = selection_offset[menu_cursor], .offset_y = 0};
    render_str(new_prompt, g, s, strings[0], sizes[0]);
    Vec4i load_prompt = {.x = 3, .y = 4, .offset_x = selection_offset[!menu_cursor], .offset_y = 0};
    render_str(load_prompt, g, s, strings[1], sizes[1]);
}

/* These comments are just notes to myself. */

// Tiles are represented by the grid. So by the values overhead the map will
// contain 1200x1800 tiles.

// Keeping things relative this way makes saving map data easy and I dont need
// to use a coordinate system. As well as being able to scale sprites.

// For the purposes of this program I will be defaulting to a 16:9 ratio
// resolution of 1280x720. And a tile size of 32x18 as it fits perfectly in that
// resolution.

// I calculated this by first choosing a relative tile height with a 16:9 ratio.
// 18 is a multiple of 9 (9 * 2). To calculate the width I do (16/9) *  18

// height = 9 * 2
// width = (16/9) * height
// columns = 1280 / width
// rows = 720 / height

// if I wanted to use a 4:3 ratio it would be something like:

// height = 3 * 4
// width = (4/3) * height
// columns = 1024 / width
// rows = 768 / height

// so 32(width)x18(height)

// So with this I can implement varying aspect ratios but for now lets
// default to 16:9
