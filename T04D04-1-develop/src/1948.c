#include <stdio.h>

int is_prime(int a);
int is_divide(int a, int b);

int main() {
  //    printf("%d", is_prime(19));

  int n, m = 0;
  if (scanf("%d", &n) != 1 || getchar() != "\n") {
    printf("n/a\n");
    return 1;
  };
  if (n < 0) {
    n *= -1;
  }
  if (n == 1 || n == 0) {
    printf("n/a\n");
  } else {
    for (int i = 1; i <= n; i++) {
      if (is_divide(n, i) == 1 && is_prime(i) == 1) {
        m = i;
      }
    }
    printf("%d\n", m);
  }
  return 0;
}

// if a % b == 0 return 1, else return 0
int is_divide(int a, int b) {
  while (a >= b) {
    a -= b;
  }
  if (a == 0)
    return 1;
  return 0;
}

// if a - is prime return 1, else return 0
int is_prime(int a) {
  if (a == 1)
    return 0;
  for (int i = 2; i * i <= a; i++) {
    if (is_divide(a, i) == 1)
      return 0;
  }
  return 1;
}