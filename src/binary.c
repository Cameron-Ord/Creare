#include "../inc/binary.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *home = NULL;

#ifdef _WIN32
const char *home_env = "USERPROFILE";
const char *slash = "\\";
#endif

#ifdef __linux__
const char *home_env = "HOME";
const char *slash = "/";
#endif

int set_home_env(void)
{
    home = getenv(home_env);
    if (!home) {
        return 0;
    }

    fprintf(stdout, "Home: %s\n", home);
    return 1;
}

int get_extension_idx(const char *arg)
{
    int i = 0;
    while (arg[i] != '\0') {
        if (arg[i] == PERIOD) {
            return i;
        }
        i++;
    }
    return -1;
}

int check_ftype(const int idx, const char *arg)
{
    if (idx < 0) {
        printf("Could not find delimiter\n");
        return 0;
    }

    const size_t len = strlen(arg) + 1;
    char buffer[len];
    int i = idx;
    int j = 0;

    while (arg[i] != '\0') {
        buffer[j] = arg[i];
        i++;
        j++;
    }

    buffer[j] = '\0';
    if (strcmp(buffer, "crx")) {
        return 1;
    }

    return 0;
}

const int HEADER_SIZE = 3;
CrxSpec read_file(const char *fn)
{
    fprintf(stdout, "Reading : %s\n", fn);
    CrxSpec spec = {0};
    int read;

    FILE *fptr = fopen(fn, "rb");
    if (!fptr) {
        fprintf(stderr, "Failed to open file in read mode! Error: %s\n",
                strerror(errno));
        return spec;
    }

    char header[HEADER_SIZE + 1];
    char req_header[] = {'C', 'R', 'X'};
    read = fread(header, sizeof(char), 3, fptr);
    if (read != 3 || ferror(fptr)) {
        fprintf(stderr, "Could not read file! Error: %s\n", strerror(errno));
        fclose(fptr);
        return spec;
    }
    header[HEADER_SIZE] = '\0';
    fprintf(stdout, "HEADER : %s\n", header);

    if (memcmp(header, req_header, 3) != 0) {
        fprintf(stderr, "Incorrect file header!\n");
        fclose(fptr);
        return spec;
    }

    read = fread(&spec, sizeof(CrxSpec), 1, fptr);
    if (read != 1 || ferror(fptr)) {
        fprintf(stderr, "Could not read file! Error: %s\n", strerror(errno));
        fclose(fptr);
        return spec;
    }

    fclose(fptr);

    spec.valid = 1;
    return spec;
}

CrxSpec create_file(const char *fn)
{
    fprintf(stdout, "Creating : %s\n", fn);
    CrxSpec spec = {0};
    int written;

    char *file_path = NULL;
    const char *directory = "Documents";

    const size_t home_length = strlen(home);
    const size_t fn_length = strlen(fn);
    const size_t dir_length = strlen(directory);
    const size_t slash_length = strlen(slash)*2;
    const size_t ext_length = strlen(".crx");

    const size_t size = home_length + fn_length + dir_length + slash_length + ext_length + 1;

    file_path = malloc(size);
    if (!file_path) {
        fprintf(stderr, "Malloc() failed! Error: %s\n", strerror(errno));
        return spec;
    }

    if (!snprintf(file_path, size, "%s%s%s%s%s%s", home, slash, directory, slash, fn, ".crx")) {
        fprintf(stderr, "snprintf() failed! Error: %s\n", strerror(errno));
        free(file_path);
        return spec;
    }

    printf("Opening file at : %s\n", file_path);
    FILE *fptr = fopen(file_path, "wb");
    if (!fptr) {
        fprintf(stderr, "Failed to open file in write mode! Error: %s\n",
                strerror(errno));
        return spec;
    }

    const char header[] = {'C', 'R', 'X'};
    written = fwrite(header, sizeof(char), 3, fptr);
    if (written != 3 || ferror(fptr)) {
        fprintf(stderr, "Failed to write to file! Error: %s\n",
                strerror(errno));
        fclose(fptr);
        return spec;
    }

    written = fwrite(&spec, sizeof(CrxSpec), 1, fptr);
    if (written != 1 || ferror(fptr)) {
        fprintf(stderr, "Failed to write to file! Error: %s\n",
                strerror(errno));
        fclose(fptr);
        return spec;
    }

    fclose(fptr);

    spec.valid = 1;
    return spec;
}
