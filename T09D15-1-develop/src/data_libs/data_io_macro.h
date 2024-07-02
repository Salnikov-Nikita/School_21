#ifndef DATA_IO_MACRO_H
#define DATA_IO_MACRO_H

#include <stdio.h>

#define INPUT(data, n, format)      \
    for (int i = 0; i < (n); i++) { \
        scanf(format, &(data)[i]);  \
    }

#define OUTPUT(data, n, format)        \
    for (int i = 0; i < (n); i++) {    \
        printf(format, (data)[i]);     \
        if (i + 1 != (n)) printf(" "); \
    }

#endif
