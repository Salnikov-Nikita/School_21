#include <stdio.h>
#define LEN 100
#define SUCCESS 1
#define ERROR_INPUT 0

/*
    Беззнаковая целочисленная длинная арифметика
    с использованием массивов.
    Ввод:
     * 2 длинных числа в виде массивов до 100 элементов
     * В один элемент массива нельзя вводить число > 9
    Вывод:
     * Результат сложения и разности чисел-массивов
    Пример:
     * 1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 6 1
       2 9

       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 9 0
       1 9 4 4 6 7 4 4 0 7 3 7 0 9 5 5 1 3 2
*/

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length);
int input(int *buffer, int *len_array);
void output(int *buffer, int len_array);
int check_max(int *buffer1, int *buffer2, int len_array);
void shift(int *buff1, int *len1, int *buff2, int *len2);

int main(void) {
    int data_1[LEN + 1], data_2[LEN + 1], data_result_1[LEN + 1], data_result_2[LEN + 1];
    int len_array_1, len_array_2, len_result_1, len_result_2;
    int check = input(data_1, &len_array_1) && input(data_2, &len_array_2);
    if (check) {
        shift(data_1, &len_array_1, data_2, &len_array_2);
        sum(data_1, len_array_1, data_2, len_array_2, data_result_1, &len_result_1);
        if (len_array_1 < len_array_2) {
            output(data_result_1, len_result_1);
            printf("\nn/a");
        } else if (len_array_1 == len_array_2 && check_max(data_1, data_2, len_array_2) == 0) {
            output(data_result_1, len_result_1);
            printf("\nn/a");

        } else {
            output(data_result_1, len_result_1);
            sub(data_1, len_array_1, data_2, len_array_2, data_result_2, &len_result_2);
            printf("\n");
            output(data_result_2, len_result_2);
        }
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *a, int *len_array) {
    int r = SUCCESS;
    int *p = a;
    char c;
    while (p - a < LEN) {
        if (scanf("%d%c", p, &c) != 2 || (c != ' ' && c != '\n') || *p > 9 || *p < 0) {
            r = ERROR_INPUT;
            break;
        }
        if (c == '\n') break;
        p++;
    }
    *len_array = p - a + 1;
    if (*len_array > LEN) {
        r = ERROR_INPUT;
    }
    return r;
}

void output(int *a, int len_array) {
    while (len_array > 1 && *a == 0) {
        a++;
        len_array--;
    }
    for (int *p = a; p - a < len_array; p++) {
        if (p - a != len_array - 1)
            printf("%d ", *p);
        else
            printf("%d", *p);
    }
}

// ONLY FOR LEN1==LEN2 ARRAYS
int check_max(int *buffer1, int *buffer2, int len_array) {
    int r = SUCCESS;
    int *p = buffer1, *q = buffer2;
    while (*p == *q && q - buffer2 < len_array - 1) {
        p++;
        q++;
    }
    if (*p - *q < 0) {
        r = ERROR_INPUT;
    }
    return r;
}

void shift(int *buff1, int *len1, int *buff2, int *len2) {
    if (*len1 >= *len2) {
        for (int i = *len1; i > 0; i--) {
            *(buff1 + i) = *(buff1 + i - 1);
        }
        *buff1 = 0;
        *len1 += 1;
        for (int i = 0; i < *len2; i++) {
            *(buff2 + *len1 - 1 - i) = *(buff2 + *len2 - 1 - i);
        }
        for (int i = 0; i < *len1 - *len2; i++) *(buff2 + i) = 0;
        *len2 = *len1;
    } else {
        shift(buff2, len2, buff1, len1);
    }
}

void sum(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    for (int i = 0; i < len2; i++) {
        *(result + i) = 0;
    }
    for (int i = len1 - 1; i > 0; i--) {
        *(result + i) += (*(buff1 + i) + *(buff2 + i));
        *(result + i - 1) += *(result + i) / 10;
        *(result + i) = *(result + i) % 10;
    }
    *result_length = len1;
}

void sub(int *buff1, int len1, int *buff2, int len2, int *result, int *result_length) {
    for (int i = 0; i < len2; i++) {
        *(result + i) = 0;
    }
    for (int i = len1 - 1; i > 0; i--) {
        *(result + i) += (*(buff1 + i) - *(buff2 + i));
        *(result + i - 1) -= *(result + i) < 0;
        *(result + i) = (*(result + i) + 10) % 10;
    }
    *result_length = len1;
}