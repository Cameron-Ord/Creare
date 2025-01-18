#ifndef FONT_H
#define FONT_H

struct CharTable {
  int x, y;
};

typedef struct CharTable CharTable;

void char_set_table(void);
CharTable table_get_char(const char c);
#endif
