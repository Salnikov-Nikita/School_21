#include "draw.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char **calloc_matrix(int height, int width) {
    char **matrix;
    matrix = (char **)calloc(height, sizeof(char *));
    for (int y = 0; y < height; y++) matrix[y] = (char *)calloc(width, sizeof(char));
    return matrix;
}

void init_graph(char **graph, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            graph[y][x] = POINT;
        }
    }
}

void draw_graph(char **graph, int height, int width) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            putchar(graph[y][x]);
        }
        putchar('\n');
    }
}

void free_matrix(char **graph, int height) {
    for (int y = 0; y < height; y++) free(graph[y]);
    free(graph);
}