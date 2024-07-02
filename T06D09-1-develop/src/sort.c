#include <stdio.h>
#define N 10
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int *a);
void output(int *a);
void bubble_sort(int *a);

int main(void) {
    int data[N];
    int check = input(data);
    if (check) {
        bubble_sort(data);
        output(data);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *a) {
    int r = SUCCESS;
    char c;
    for (int *p = a; p - a < N; p++)
        if (scanf("%d%c", p, &c) != 2 || (c != ' ' && c != '\n')) {
            r = ERROR_INPUT;
            break;
        }

    return r;
}

void output(int *a) {
    for (int *p = a; p - a < N; p++) {
        if (p - a != N - 1)
            printf("%d ", *p);
        else
            printf("%d", *p);
    }
}

void bubble_sort(int *a) {
    for (int *p = a; p - a < N - 1; p++) {
        for (int *g = p + 1; g - a < N; g++) {
            if (*p > *g) {
                int buff = *p;
                *p = *g;
                *g = buff;
            }
        }
    }
}