#include "data_stat.h"

#include <math.h>

double max(double *data, int n) {
    double mx = data[0];
    for (int i = 1; i < n; i++) {
        mx = mx < data[i] ? data[i] : mx;
    }
    return mx;
}
double min(double *data, int n) {
    double mn = data[0];
    for (int i = 1; i < n; i++) {
        mn = mn > data[i] ? data[i] : mn;
    }
    return mn;
}
double mean(double *data, int n) {
    double sm = data[0];
    for (int i = 1; i < n; i++) {
        sm += data[i];
    }
    return sm / n;
}
double variance(double *data, int n) {
    double sm = 0;
    double mea = mean(data, n);
    for (int i = 1; i < n; i++) {
        sm += pow(data[i] - mea, 2);
    }
    return sm / n;
}