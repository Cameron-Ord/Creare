#include "../inc/binary.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

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
    char         buffer[len];
    int          i = idx;
    int          j = 0;

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
crx_spec  read_file(const char *fn)
{
    fprintf(stdout, "Reading : %s\n", fn);
    crx_spec spec = {0};
    int      read;

    FILE *fptr = fopen(fn, "rb");
    if (!fptr) {
        fprintf(stderr, "Failed to open file in read mode! Error: %s\n",
                strerror(errno));
        return spec;
    }

    char header[HEADER_SIZE + 1];
    char req_header[] = {'C', 'R', 'X'};
    read              = fread(header, sizeof(char), 3, fptr);
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

    read = fread(&spec, sizeof(crx_spec), 1, fptr);
    if (read != 1 || ferror(fptr)) {
        fprintf(stderr, "Could not read file! Error: %s\n", strerror(errno));
        fclose(fptr);
        return spec;
    }

    fclose(fptr);

    spec.valid = 1;
    return spec;
}

crx_spec create_file(const char *fn)
{
    fprintf(stdout, "Creating : %s\n", fn);
    crx_spec spec = {0};
    int      written;

    FILE *fptr = fopen(fn, "wb");
    if (!fptr) {
        fprintf(stderr, "Failed to open file in write mode! Error: %s\n",
                strerror(errno));
        return spec;
    }

    const char header[] = {'C', 'R', 'X'};
    written             = fwrite(header, sizeof(char), 3, fptr);
    if (written != 3 || ferror(fptr)) {
        fprintf(stderr, "Failed to write to file! Error: %s\n",
                strerror(errno));
        fclose(fptr);
        return spec;
    }

    written = fwrite(&spec, sizeof(crx_spec), 1, fptr);
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
