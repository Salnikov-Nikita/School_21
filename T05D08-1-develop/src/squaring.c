#include <stdio.h>
#define NMAX 10
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main(void) {
    int n, data[NMAX];
    int check = input(data, &n);
    if (check) {
        squaring(data, n);
        output(data, n);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *a, int *n) {
    int r = SUCCESS;
    char c;
    if (scanf("%d", n) == 1 && *n <= NMAX && *n > 0) {
        for (int *p = a; p - a < *n; p++)
            if (scanf("%d%c", p, &c) != 2 || (c != ' ' && c != '\n')) {
                r = ERROR_INPUT;
                break;
            }
    } else {
        r = ERROR_INPUT;
    }
    return r;
}

void output(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        if (p - a != n - 1)
            printf("%d ", *p);
        else
            printf("%d", *p);
    }
}

void squaring(int *a, int n) {
    for (int *p = a; p - a < n; p++) {
        *p *= (*p);
    }
}