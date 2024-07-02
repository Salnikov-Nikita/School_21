#include <stdio.h>
#include <stdlib.h>

int fib(int n);

int main() {
  //    printf("%d", is_prime(19));

  int n;
  if ((scanf("%d", &n) != 1 || getchar() == '\n') && n > 0) {
    printf("%d\n", fib(n));
  } else {
    printf("n/a\n");
  }
  return 0;
}

int fib(int n) {
  if (n == 1 || n == 2)
    return 1;
  return fib(n - 1) + fib(n - 2);
}