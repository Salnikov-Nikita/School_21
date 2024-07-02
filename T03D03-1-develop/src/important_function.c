#include <math.h>
#include <stdio.h>
// y = 7e-3 * x^4 + ((22.8 * x^⅓ - 1e3) * x + 3) / (x * x / 2) - x * (10 + x)^(2/x) - 1.01.

double func(double x);

int main() {
    double x = 0;

    if (scanf("%lf", &x) == 1) {
            printf("%.1lf\n", func(x));
    } else {
        printf("n/a\n");
    }
    return 0;
}

double func(double x) {
    return 0.007 * pow(x, 4) + ((22.8 * pow(x, 1.0 / 3) - 1000) * x + 3) / (x * x / 2.0) -
           x * pow((10 + x), (2.0 / x)) - 1.01;
}
