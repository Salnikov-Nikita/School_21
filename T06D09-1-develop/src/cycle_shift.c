#include <stdio.h>
#define SUCCESS 1
#define ERROR_INPUT 0
#define NMAX 10

int input(int *a, int *n, int *k);
void output(int *a, int n);
void slide(int *a, int n, int k);

int main(void) {
    int data[NMAX + 1];
    int n, k;
    int check = input(data, &n, &k);
    if (check) {
        slide(data, n, k);
        output(data, n);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *a, int *n, int *k) {
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
    if (scanf("%d", k) != 1 || r != SUCCESS) {
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

void slide(int *a, int n, int k) {
    int sl = k % n;
    if (sl < 0) {
        sl += n;
    }
    for (int i = 0; i < sl; i++) {
        int buf = *a;
        for (int *p = a; p - a - 1 < n; p++) {
            *p = *(p + 1);
        }
        *(a + n - 1) = buf;
    }
}