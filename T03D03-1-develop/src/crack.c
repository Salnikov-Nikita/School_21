#include <stdio.h>

int main() {
    double x, y;
    if (scanf("%lf", &x) != 1) {
        printf("n/a\n");
    } else if (scanf("%lf", &y) != 1) {
        printf("n/a\n");
    } else {
        if (x * x + y * y < 25) {
            printf("GOTCHA\n");
        } else {
            printf("MISS\n");
        }
    }
    return 0;
}