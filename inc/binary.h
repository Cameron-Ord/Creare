#ifndef BINARY_H
#define BINARY_H

typedef struct CrxSpec
{
    int x, j, g, valid;
} CrxSpec;

int set_home_env(void);
CrxSpec create_file(const char *fn);
CrxSpec read_file(const char *fn);
int get_extension_idx(const char *arg);
int check_ftype(const int idx, const char *arg);
#endif // BINARY_H
