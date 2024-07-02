#include <math.h>
#include <stdio.h>
#define NMAX 10
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);

void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int check = input(data, &n);
    if (check) {
        output(data, n);
        output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));
    } else {
        printf("n/a");
        return 1;
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
        printf("%d", *p);
        if (p - a + 1 < n) printf(" ");
    }
}

int max(int *a, int n) {
    int max = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p > max) max = *p;
    }
    return max;
}

int min(int *a, int n) {
    int min = *a;
    for (int *p = a; p - a < n; p++) {
        if (*p < min) min = *p;
    }
    return min;
}

double mean(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += (*p);
    }
    return sum / n;
}

double variance(int *a, int n) {
    double sum = 0;
    for (int *p = a; p - a < n; p++) {
        sum += pow((*p) - mean(a, n), 2);
    }
    return sum / n;
}

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("\n%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}