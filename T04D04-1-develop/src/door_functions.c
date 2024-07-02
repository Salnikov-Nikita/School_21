#include <float.h>
#include <math.h>
#include <stdio.h>

const double PI = 3.1415926535897931;

double a[42][4];

int main(void) {
  for (int i = 0; i < 42; ++i) {
    double x = i / 41.0 * (PI * 2) - PI;
    a[i][0] = x;
    a[i][1] = 1 / (1 + x * x);
    a[i][2] = sqrt(sqrt(1 + 4 * x * x) - x * x - 1);
    a[i][3] = 1 / (x * x);
  }

  for (int i = 0; i < 42; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (j)
        fputs(" | ", stdout);
      if (isfinite(a[i][j])) {
        printf("%.7f", a[i][j]);
      } else {
        putchar('-');
      }
    }
    putchar('\n');
  }

  for (int j = 1; j < 4; ++j) {
    printf("FUNCTION %d\n", j);
    double lo = DBL_MAX, hi = -DBL_MAX;
    for (int i = 0; i < 42; ++i) {
      if (!isfinite(a[i][j]))
        continue;
      if (a[i][j] < lo)
        lo = a[i][j];
      if (a[i][j] > hi)
        hi = a[i][j];
    }
    for (int i = 0; i < 42; ++i) {
      if (isfinite(a[i][j])) {
        int k = (int)round((a[i][j] - lo) / (hi - lo) * 20);
        for (int j = 0; j < k; ++j) {
          putchar(' ');
        }
        putchar('*');
      }
      putchar('\n');
    }
  }
}