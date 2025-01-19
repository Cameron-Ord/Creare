#include "../inc/input.h"
#include "../inc/font.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int clamp(int i, const int max, const int min)
{
    if (i < min) {
        i = min;
    }

    if (i > max) {
        i = max;
    }

    return i;
}

int insert_char(const char c, InputMap *map)
{
    const int gate = map->size + 1 > map->char_max;
    if (!gate && !not_known(c)) {
        map->size = clamp(map->size + 1, map->char_max, 1);
        char *tmp = realloc(map->input_buffer, map->size + 1);
        if (!tmp) {
            fprintf(stderr, "realloc() failed! Error: %s\n", strerror(errno));
            return 1;
        }

        map->input_buffer = tmp;
        map->input_buffer[map->char_cursor] = c;
        map->input_buffer[map->size] = '\0';
        map->char_cursor = clamp(map->char_cursor + 1, map->char_max - 1, 0);
    }
    return 1;
}

int remove_last_char(InputMap *map)
{
    const int gate = map->size - 1 <= 0;
    if (!gate) {
        map->size = clamp(map->size - 1, map->char_max, 1);
        map->input_buffer = realloc(map->input_buffer, map->size + 1);
        if (!map->input_buffer) {
            fprintf(stderr, "realloc() failed! Error: %s\n", strerror(errno));
            return 1;
        }

        map->char_cursor = clamp(map->char_cursor - 1, map->char_max - 1, 0);
        map->input_buffer[map->char_cursor] = '\0';
    } else {
        map->input_buffer[0] = '\0';
    }

    return 1;
}