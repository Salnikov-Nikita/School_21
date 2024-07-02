#include <stdio.h>

int sum(int a, int b);
int diff(int a, int b);
int mult(int a, int b);
int divv(int a, int b);

int main() {
    int a = 0, b = 0;
    char term;
    if ((scanf("%d%d%c", &a, &b, &term) != 3 || term != '\n') && term != ' ') {
        printf("n/a\n");
    } else {
        printf("%d %d %d ", sum(a, b), diff(a, b), mult(a, b));
        if (b != 0) {
            printf("%d\n", divv(a, b));
        }
        else {
            printf("n/a\n");
        }
    }
    return 0;
}

int sum(int a, int b) { return a + b; }
int diff(int a, int b) { return a - b; }
int mult(int a, int b) { return a * b; }
int divv(int a, int b) { return a / b; }
