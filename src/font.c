#include "../inc/font.h"
#include "../inc/render.h"
#include <stdio.h>
#include <string.h>

// Size of ascii chars
CharTable char_table[128];

const int char_width = 16;
const int char_height = 16;

const int table_rows = 6 * char_height;
const int table_cols = 5 * char_width;

const int row_offsets[] = {0, table_rows};
const int col_offsets[] = {0, table_cols, table_cols * 2};

const char *char_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

void char_set_table(void)
{
    const size_t length = strlen(char_str);

    int row = 0;
    int col = 0;
    for (size_t i = 0; i < length; i++) {
        if (col >= table_cols) {
            col = 0;
            row += char_height;
        }

        if (row >= table_rows) {
            break;
        }

        const int access = char_str[i];
        char_table[access] = (CharTable){col, row};

        col += char_width;
    }
}

CharTable table_get_char(const char c)
{
    const int access = c;
    return char_table[access];
}

TileDm get_font_sizing(void) { return (TileDm){.w = char_width, .h = char_height}; }
