#ifndef FONT_H
#define FONT_H
#include "vectors.h"

int not_known(const char c);
void char_set_table(void);
Vec2i table_get_char(const char c);
Vec2i get_font_sizing(void);
#endif
