#include <stdio.h>
#include <stdlib.h>
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int *a, int len);
void output(int *a, int len);
void bubble_sort(int *a, int len);

int main(void) {
    int n;
    int *data;
    if (scanf("%d", &n) == 1 && n > 0) {
        data = (int *)calloc(n, sizeof(int));
        if (data != NULL) {
            int check = input(data, n);
            if (check) {
                bubble_sort(data, n);
                output(data, n);
            } else {
                printf("n/a");
            }
            free(data);
            data = 0;
        }
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *a, int len) {
    int r = SUCCESS;
    char c;
    for (int *p = a; p - a < len; p++)
        if (scanf("%d%c", p, &c) != 2 || (c != ' ' && c != '\n')) {
            r = ERROR_INPUT;
            break;
        }

    return r;
}

void output(int *a, int len) {
    for (int *p = a; p - a < len; p++) {
        if (p - a != len - 1)
            printf("%d ", *p);
        else
            printf("%d", *p);
    }
}

void bubble_sort(int *a, int len) {
    for (int *p = a; p - a < len - 1; p++) {
        for (int *g = p + 1; g - a < len; g++) {
            if (*p > *g) {
                int buff = *p;
                *p = *g;
                *g = buff;
            }
        }
    }
}