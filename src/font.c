#include "../inc/font.h"
#include "../inc/render.h"
#include <string.h>
#include <stdio.h>

// Size of ascii chars
CharTable char_table[128];
const TileDm font_size = {16, 16};
const char *char_str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

void char_set_table(void) {
  const int table_rows = 6 * font_size.h;
  const int table_cols = 5 * font_size.w;
  const size_t length = strlen(char_str);

  int row = 0;
  int col = 0;
  for (size_t i = 0; i < length; i++) {
    if (col >= table_cols) {
      col = 0;
      row += font_size.h;
    }

    if (row >= table_rows) {
      break;
    }

    const int access = char_str[i];
    char_table[access] = (CharTable){col, row};

    col += font_size.w;
  }
}

CharTable table_get_char(const char c) {
  const int access = c;
  return char_table[access];
}

TileDm get_font_sizing(void){
  return font_size;
}
