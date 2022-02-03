#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wordexp.h>

#define LENLINE 1024

typedef enum testresult_t {
    TEST_PASSED = true,
    TEST_FAILED = false,
} testresult_t;

int fcountlines(FILE *fp) {
    char c;
    int count = 0;

    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n')
            count = count + 1;

    rewind(fp);

    return count;
}

void fopen_save(FILE **stream, const char *path) {
    wordexp_t path_exp;
    wordexp(path, &path_exp, 0);

    *stream = fopen(path_exp.we_wordv[0], "r");
    wordfree(&path_exp);

    if (stream == NULL) {
        fprintf(stderr, "Could not open file %s\n", path);
        exit(EXIT_FAILURE);
    }
}

int read_input_lines(char (**_lines)[LENLINE], char *path) {
    FILE *stream = NULL;
    fopen_save(&stream, path);

    int n_lines = 0;
    n_lines = fcountlines(stream);
    char *line = NULL;
    size_t len = 0;

    char(*lines)[LENLINE];
    lines = calloc(n_lines, LENLINE);

    for (int i = 0; i < n_lines; i++) {
        getline(&line, &len, stream);
        strncpy(lines[i], line, len);
    }
    fclose(stream);
    *_lines = lines;
    return n_lines;
}
