#include "calculation.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "draw.h"

double counter(int *output_str, HEAD *head, double x, int len) {
    double num1, num2;
    for (int i = 0; i < len; ++i) {
        if (output_str[i] == 'x') {
            pushing(x, head);
        } else if (output_str[i] <= 0) {
            pushing(-output_str[i], head);
        } else if (output_str[i] == 'n') {
            num1 = pop(head);
            pushing(-num1, head);
        } else if (output_str[i] == '+') {
            num2 = pop(head);
            num1 = pop(head);
            pushing(num1 + num2, head);
        } else if (output_str[i] == '-') {
            num2 = pop(head);
            num1 = pop(head);
            pushing(num1 - num2, head);
        } else if (output_str[i] == '*') {
            num2 = pop(head);
            num1 = pop(head);
            pushing(num1 * num2, head);
        } else if (output_str[i] == '/') {
            num2 = pop(head);
            num1 = pop(head);
            pushing(num1 / num2, head);
        } else if (output_str[i] == 's') {
            num1 = pop(head);
            pushing(sin(num1), head);
        } else if (output_str[i] == 'c') {
            num1 = pop(head);
            pushing(cos(num1), head);
        } else if (output_str[i] == 't') {
            num1 = pop(head);
            pushing(tan(num1), head);
        } else if (output_str[i] == 'g') {
            num1 = pop(head);
            pushing(1 / tan(num1), head);
        } else if (output_str[i] == 'q') {
            num1 = pop(head);
            pushing(sqrt(num1), head);
        } else if (output_str[i] == 'l') {
            num1 = pop(head);
            pushing(log(num1), head);
        }
    }
    return pop(head);
}

void init(HEAD *head) { head->point = NULL; }

void pushing(double sym, HEAD *head) {
    OPERATIONS *tmp;
    tmp = head->point;
    OPERATIONS *new = (OPERATIONS *)malloc(sizeof(OPERATIONS));
    new->oper = sym;
    new->point = tmp;
    head->point = new;
}

double pop(HEAD *head) {
    double x;
    OPERATIONS *tmp = head->point;
    x = head->point->oper;
    head->point = head->point->point;
    free(tmp);
    return x;
}

void add_func_for_graph(char **graph, int height, int width, int *out, HEAD *head, int len) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double y = 25;
            y = round(12 + 12 * counter(out, head, (M_PI * x) / 20, len));
            if (y >= 0 && y < 25) graph[(int)y][x] = STAR;
        }
    }
}
