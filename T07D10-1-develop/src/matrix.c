#include <stdio.h>
#include <stdlib.h>
#define NMAX 100
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int **buffer, int len, int length_m);
int input_type_size(int *type, int *len, int *length_m);
void output(int **buffer, int len, int length_m);
void free_matrix(int type, int **buffer, int len);

int main(void) {
    int type, n, m;
    int **array = NULL;

    int static_array[NMAX][NMAX];
    int *static_array_pointers[NMAX];

    if (input_type_size(&type, &n, &m)) {
        if (type == 1) {
            for (int i = 0; i < n; i++) {
                static_array_pointers[i] = &static_array[i][0];
            }
            array = static_array_pointers;
        } else if (type == 2) {
            array = (int **)calloc(n, sizeof(int *));
            for (int i = 0; i < n; i++) {
                array[i] = (int *)calloc(m, sizeof(int));
            }
        } else if (type == 3) {
            array = (int **)calloc(n, sizeof(int *));
            int *a = (int *)calloc(n * m, sizeof(int));
            for (int i = 0; i < n; i++) {
                array[i] = &a[i * m];
            }
        } else if (type == 4) {
            array = (int **)malloc(n * sizeof(int *) + n * m * sizeof(int));
            int *a = (int *)(array + n);
            for (int i = 0; i < n; i++) {
                array[i] = &a[i * m];
            }
        }

        if (array != NULL) {
            if (input(array, n, m)) {
                output(array, n, m);
                free_matrix(type, array, n);
            } else {
                printf("n/a");
            }
        }

    } else {
        printf("n/a");
    }

    return 0;
}

int input_type_size(int *type, int *len, int *length_m) {
    int r = SUCCESS;
    char ch;
    if (scanf("%d%d%d%c", type, len, length_m, &ch) != 4 || ch != '\n') r = ERROR_INPUT;
    if (*type <= 0 || *type > 4) r = ERROR_INPUT;
    if (*type == 1 && (*len > NMAX || *length_m > NMAX)) r = ERROR_INPUT;
    return r;
}

int input(int **buffer, int len, int length_m) {
    int r = SUCCESS;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < length_m; j++) {
            if (scanf("%d", &buffer[i][j]) != 1) {
                r = ERROR_INPUT;
                break;
            }
        }
        if (r == ERROR_INPUT) {
            break;
        }
    }
    return r;
}

void output(int **buffer, int len, int length_m) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < length_m; j++) {
            printf("%d", buffer[i][j]);
            if (j != length_m - 1) printf(" ");
            if (j == length_m - 1 && i != len - 1) printf("\n");
        }
    }
}

void free_matrix(int type, int **buffer, int len) {
    if (type == 2) {
        for (int i = 0; i < len; i++) {
            free(buffer[i]);
            buffer[i] = 0;
        }
        free(buffer);
        buffer = 0;
    }
    if (type == 3) {
        free(buffer[0]);
        free(buffer);
        buffer = 0;
    }
    if (type == 4) {
        free(buffer);
        buffer = 0;
    }
}