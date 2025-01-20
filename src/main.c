#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "../inc/binary.h"
#include "../inc/font.h"
#include "../inc/gfx.h"
#include "../inc/input.h"
#include "../inc/render.h"
#include "../inc/window.h"

#define MAP_HEIGHT 1200
#define MAP_WIDTH 1800

typedef enum
{
    MENU = 0,
    CREATOR = 1,
    TAKE_INPUT = 2,
    FILE_TREE = 3
} Modes;

typedef enum
{
    NEW = 0,
    LOAD = 1
} Selections;

typedef struct MenuVars
{
    char *strings[2];
    int str_lens[2];
    int menu_cursor : 1;
    int offsets[2];
} MenuVars;

typedef struct ProgramState
{
    int mode;
} ProgramState;

// #define DFT_HEIGHT 720
// #define DFT_WIDTH 1280

const char *charsheet_fn = "chars.png";

static void update_window(const int w, const int h);
static void set_mode(int *mode, const int mode_value);
static void paint_menu(const MenuVars *v, const Vec4i *g, const Sprite *s);

int main(int argc, char **argv)
{
    if (!set_home_env()) {
        return 1;
    }

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

    Vec4i current_grid = get_sd_grids()[1];

    Sprite char_sheet = create_sprite(charsheet_fn, get_renderer());
    if (!char_sheet.valid) {
        return 1;
    }

    char_set_table();

    char *input_buffer = malloc(1);
    if (!input_buffer) {
        fprintf(stderr, "malloc() failed! Error: %s\n", strerror(errno));
        return 1;
    }
    input_buffer[0] = '\0';

    MenuVars menu = {{"NEW", "LOAD"}, {3, 4}, 0, {0, 4 * 16}};
    ProgramState state = {MENU};
    InputMap input_mapper = {.input_buffer = input_buffer, .char_cursor = 0, .size = 1, .char_max = get_sd_grids()[0].x - 1};

    int running = 1;
    const int tpf = (1000.0 / 30);
    uint64_t frame_start;
    int frame_time;

    SDL_EnableScreenSaver();
    SDL_StopTextInput();

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

            case SDL_TEXTINPUT:
            {
                const char *text = e.text.text;
                const size_t text_length = strlen(text);

                for (size_t i = 0; i < text_length; i++) {
                    insert_char(text[i], &input_mapper);
                }

            } break;

            case SDL_KEYDOWN:
            {
                const uint32_t keycode = e.key.keysym.sym;
                const uint16_t keymod = e.key.keysym.mod;

                switch (state.mode) {
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
                        switch (menu.menu_cursor) {
                        case NEW:
                        {
                            set_mode(&state.mode, TAKE_INPUT);
                            SDL_StartTextInput();
                        } break;

                        case LOAD:
                        {
                            set_mode(&state.mode, FILE_TREE);
                        } break;
                        }

                    } break;

                    case SDLK_UP:
                    {
                        menu.menu_cursor = !menu.menu_cursor;
                    } break;

                    case SDLK_DOWN:
                    {
                        menu.menu_cursor = !menu.menu_cursor;
                    } break;
                    }
                } break;

                case FILE_TREE:
                {
                    switch (keycode) {
                    default:
                        break;
                    }
                } break;

                case TAKE_INPUT:
                {
                    switch (keycode) {
                    default:
                        break;

                    case SDLK_BACKSPACE:
                    {
                        remove_last_char(&input_mapper);
                    } break;

                    case SDLK_RETURN:
                    {
                        SDL_StopTextInput();
                        create_file(input_mapper.input_buffer);
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

        //Render stuff depending on the current mode.

        switch (state.mode) {
        default:
            break;
        case MENU:
        {
            paint_menu(&menu, &current_grid, &char_sheet);
        } break;

        case CREATOR:
        {

        } break;

        case TAKE_INPUT:
        {
            Vec4i g = get_sd_grids()[0];
            Vec4i pos = {.x = 1, .y = 0.5 * g.y, .w = 0, .h = 0};
            if (input_mapper.size >= 1) {
                render_str(pos, &g, &char_sheet, input_mapper.input_buffer, input_mapper.size);
            }
        } break;

        case FILE_TREE:
        {

        } break;
        }

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

static void set_mode(int *mode, const int mode_value)
{
    *mode = mode_value;
}

static void paint_menu(const MenuVars *v, const Vec4i *g, const Sprite *s)
{
    Vec4i new_prompt = {.x = 3, .y = 3, .w = 0, .h = v->offsets[v->menu_cursor]};
    render_str(new_prompt, g, s, v->strings[0], v->str_lens[0]);
    Vec4i load_prompt = {.x = 3, .y = 4, .w = 0, .h = v->offsets[!v->menu_cursor]};
    render_str(load_prompt, g, s, v->strings[1], v->str_lens[1]);
}

static void update_window(const int w, const int h)
{
    SDL_SetWindowSize(get_window()->w, w, h);
    get_window()->width = w;
    get_window()->height = h;
    set_window_sd(get_window());
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
