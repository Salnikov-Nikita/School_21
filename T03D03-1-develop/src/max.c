#include <stdio.h>

int max(int a, int b);

int main() {
    int a = 0, b = 0;
    if ((scanf("%d%d", &a, &b) != 2 || getchar() != '\n')) {
        printf("n/a\n");
    } else {
        printf("%d\n", max(a, b));
    }
    return 0;
}

int max(int a, int b) { 
    return a > b ? a : b;
 }
