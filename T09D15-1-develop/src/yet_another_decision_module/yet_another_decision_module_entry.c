#include <stdio.h>
#include <stdlib.h>

#include "../data_libs/data_io.h"
#include "decision.h"

int main() {
    double *data = NULL;
    int n;
    if (scanf("%d", &n) != 1 || n != 0) {
        printf("n/a");
    } else {
        data = (double *)calloc(n, sizeof(double));
        input(data, n);

        if (make_decision(data, n))
            printf("YES");
        else
            printf("NO");

        if (data != NULL) free(data);
    }
    return 0;
}
