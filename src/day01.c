#include "util.h"
#include <stdbool.h>
#include <stdio.h>
#include <wordexp.h>

#define WINDOW_SIZE 4

struct window_t {
    long data[WINDOW_SIZE];
    size_t head;
    size_t tail;
};

void window_push_back(struct window_t *window, long value) {
    window->data[window->tail++] = value;
    if (window->tail == WINDOW_SIZE) {
        window->tail = 0;
    }
}

void window_pop_front(struct window_t *window) {
    window->head++;
    if (window->head == WINDOW_SIZE) {
        window->head = 0;
    }
}

long window_get(struct window_t *window, size_t index) {
    return window->data[(index + window->head) % WINDOW_SIZE];
}

int count_increasing_sum(int n_lines, char (*lines)[LENLINE]) {
    int count = 0;
    long val = 0;
    long prev = 0;
    struct window_t window = {{0}, 0, 0};

    for (int i = 0; i < 4; i++) {
        val = strtol(lines[i], NULL, 10);
        window_push_back(&window, val);
    }

    for (int i = 4; i < n_lines; i++) {
        val = strtol(lines[i], NULL, 10);
        if ((window_get(&window, 0) + window_get(&window, 1) +
             window_get(&window, 2)) <
            (window_get(&window, 1) + window_get(&window, 2) +
             window_get(&window, 3)))
            count++;
        window_push_back(&window, val);
        window_pop_front(&window);
    }

    if ((window_get(&window, 0) + window_get(&window, 1) +
         window_get(&window, 2)) <
        (window_get(&window, 1) + window_get(&window, 2) +
         window_get(&window, 3)))
        count++;

    return count;
}

int count_increasing(int n_lines, char (*lines)[LENLINE]) {
    long val = 0;
    long prev = 0;
    int count = 0;

    prev = strtol(lines[0], NULL, 10);

    for (int i = 0; i < n_lines; i++) {
        val = strtol(lines[i], NULL, 10);
        if (val > prev)
            count++;
        prev = val;
    }
    return count;
}

long part1(char *path) {
    char(*lines)[LENLINE] = NULL;
    int n_lines = read_input_lines(&lines, path);

    int solution = 0;
    solution = count_increasing(n_lines, lines);

    free(lines);

    return solution;
}

long part2(char *path) {
    char(*lines)[LENLINE] = NULL;
    int n_lines = read_input_lines(&lines, path);

    int solution = 0;
    solution = count_increasing_sum(n_lines, lines);

    free(lines);

    return solution;
}

testresult_t test_part1(char *path) {
    char(*lines)[LENLINE] = NULL;
    int n_lines = read_input_lines(&lines, path);
    long expected = 7;

    int solution = 0;
    solution = count_increasing(n_lines, lines);

    free(lines);

    return (solution == expected);
}

testresult_t test_part2(char *path) {
    char(*lines)[LENLINE] = NULL;
    int n_lines = read_input_lines(&lines, path);
    long expected = 5;

    int solution = 0;
    solution = count_increasing_sum(n_lines, lines);

    free(lines);

    return (solution == expected);
}

int main() {
    testresult_t test_result =
        test_part1("~/Projects/advent-of-code/input/day01.test");
    if (!test_result) {
        fprintf(stderr, "Part 1 did not pass test!\n");
        exit(EXIT_FAILURE);
    }

    int solution = part1("~/Projects/advent-of-code/input/day01.input");
    printf("Solution to part 1: %d\n", solution);

    test_result = test_part2("~/Projects/advent-of-code/input/day01.test");
    if (!test_result) {
        fprintf(stderr, "Part 2 did not pass test!\n");
        exit(EXIT_FAILURE);
    }

    solution = part2("~/Projects/advent-of-code/input/day01.input");
    printf("Solution to part 2: %d\n", solution);
}
