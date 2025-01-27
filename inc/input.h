#ifndef INPUT_H
#define INPUT_H

typedef struct InputMap
{
    char *input_buffer;
    int char_cursor, size;
    int char_max;
} InputMap;

int insert_char(const char c, InputMap *map);
int remove_last_char(InputMap *map);
#endif // INPUT_H