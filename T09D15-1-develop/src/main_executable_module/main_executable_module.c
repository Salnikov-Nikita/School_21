#include <stdio.h>
#include <stdlib.h>

#ifdef USE_MACROS
#include "../data_libs/data_io_macro.h"
#define INPUT_DATA(data, n) INPUT(data, n, "%lf")
#define OUTPUT_DATA(data, n) OUTPUT(data, n, "%.2lf")
#else
#include "../data_libs/data_io.h"
#define INPUT_DATA(data, n) input(data, n)
#define OUTPUT_DATA(data, n) output(data, n)
#endif

#include "../data_libs/data_sort.h"
#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"

int main() {
    double *data = NULL;
    int n;
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("n/a");
    } else {
        data = (double *)calloc(n, sizeof(double));
        // io
        printf("LOAD DATA...\n");
        INPUT_DATA(data, n);
        // io
        printf("RAW DATA:\n\t");
        OUTPUT_DATA(data, n);
        // data_process
        printf("\nNORMALIZED DATA:\n\t");
        normalization(data, n);
        OUTPUT_DATA(data, n);
        // sort
        printf("\nSORTED NORMALIZED DATA:\n\t");
        sort(data, n);
        OUTPUT_DATA(data, n);
        // decision
        printf("\nFINAL DECISION:\n\t");
        if (make_decision(data, n))
            printf("YES");
        else
            printf("NO");
        free(data);
    }

    return 0;
}
