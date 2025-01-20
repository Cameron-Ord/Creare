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

#define SCREEN_HEIGHT 270
#define SCREEN_WIDTH 480

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
    int menu_cursor;
    int offsets[2];
} MenuVars;

typedef struct ProgramState
{
    int mode;
} ProgramState;

// #define DFT_HEIGHT 720
// #define DFT_WIDTH 1280

const char *charsheet_fn = "chars.png";

static void update_window(const int vp_w, const int vp_h);
static void set_mode(int *mode, const int mode_value);
static SDL_Rect update_viewport();

static SDL_Rect update_viewport()
{
    int w = get_window()->width, h = get_window()->height;
    float ratio = 16.0f / 9.0f;

    int updated_width = w;
    int updated_height = (int)(w / ratio);

    if (updated_height > h) {
        updated_height = h;
        updated_width = (int)(h * ratio);
    }

    updated_width = (updated_width / 32) * 32;
    updated_height = (updated_height / 18) * 18;

    int x = (w - updated_width) / 2;
    int y = (h - updated_height) / 2;

    return (SDL_Rect){x, y, updated_width, updated_height};
}

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

    if (!create_win(640, 360)) {
        SDL_Quit();
        return 1;
    }
    SDL_Rect vp = update_viewport();
    grid_update_window(vp.w, vp.h);
    grid_update_sprite_size(vp.w, vp.h);

    if (!create_renderer(get_window())) {
        SDL_DestroyWindow(get_window()->w);
        SDL_Quit();
        return 1;
    }

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

    MenuVars menu = {0, {0, 64}};
    ProgramState state = {MENU};
    InputMap input_mapper = {.input_buffer = input_buffer, .char_cursor = 0, .size = 1, .char_max = (get_grid()->w / 4) - 1};

    int running = 1;
    const int tpf = (1000.0 / 30);
    uint64_t frame_start;
    int frame_time;

    SDL_EnableScreenSaver();
    SDL_StopTextInput();
    SDL_ShowWindow(get_window()->w);
    while (running) {
        frame_start = SDL_GetTicks64();

        SDL_RenderSetViewport(get_renderer()->r, &vp);

        render_base_bg();
        render_clear();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            default:
                break;
            case SDL_WINDOWEVENT:
            {
                switch (e.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                {
                    vp = update_viewport();
                    update_window(vp.w, vp.h);
                } break;

                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    vp = update_viewport();
                    update_window(vp.w, vp.h);
                } break;
                }
            } break;

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
                        menu.menu_cursor = NEW;
                    } break;

                    case SDLK_DOWN:
                    {
                        menu.menu_cursor = LOAD;
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
                        if (create_file(input_mapper.input_buffer).valid) {
                            set_mode(&state.mode, CREATOR);
                        }
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
            RenderStr string_new = {{1, 2}, "NEW", 3, {4, 2}, get_grid(), menu.offsets[menu.menu_cursor]};
            render_str(&string_new, &char_sheet);

            RenderStr string_load = {{1, 3}, "LOAD", 4, {4, 2}, get_grid(), menu.offsets[!menu.menu_cursor]};
            render_str(&string_load, &char_sheet);

        } break;

        case CREATOR:
        {
            render_grid(get_grid());
        } break;

        case TAKE_INPUT:
        {
            RenderStr string_load = {{1, 3}, input_buffer, input_mapper.size, {4, 2}, get_grid(), 0};
            render_str(&string_load, &char_sheet);
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

static void update_window(const int vp_w, const int vp_h)
{
    SDL_GetWindowSize(get_window()->w, &get_window()->width, &get_window()->height);
    grid_update_window(vp_w, vp_h);
    grid_update_sprite_size(vp_w, vp_h);
}
