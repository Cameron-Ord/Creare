#include "../inc/font.h"
#include "../inc/render.h"
#include <stdio.h>
#include <string.h>

// Size of ascii chars
CharTable char_table[128];

const int char_width = 16;
const int char_height = 16;

const int table_rows = 12 * char_height;
const int table_cols = 13 * char_width;

const char *char_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";

int not_known(const char c){
    for(size_t i = 0; i < strlen(char_str); i++){
        if(c == char_str[i]){
            return 0;
        }
    }
    return 1;
}

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

        if (row > table_rows) {
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
