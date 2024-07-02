/*
    Search module for the desired value from data array.

    Returned value must be:
        - "even"
        - ">= mean"
        - "<= mean + 3 * sqrt(variance)"
        - "!= 0"

        OR

        0
*/
#include <math.h>
#include <stdio.h>
#define NMAX 30
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int *a, int *n);
double mean(int *a, int n);
double variance(int *a, int n);
int find_number(int *a, int n, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    int check = input(data, &n);
    if (check) {
        printf("%d", find_number(data, n, mean(data, n), variance(data, n)));
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

int find_number(int *a, int n, double mean_v, double variance_v) {
    for (int *p = a; p - a < n; p++) {
        if (*p % 2 == 0 && *p >= mean_v && *p != 0 && *p <= mean_v + 3 * sqrt(variance_v)) {
            return *p;
        }
    }
    return 0;
}