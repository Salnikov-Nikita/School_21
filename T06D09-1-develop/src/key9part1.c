#include <stdio.h>
#define NMAX 10
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

int main() {
    int n, data[NMAX], new_data[NMAX];

    int check = input(data, &n);
    if (check) {
        int sum = sum_numbers(data, n);
        if (sum > 0) {
            int numbers = find_numbers(data, n, sum, new_data);
            printf("%d\n", sum);
            output(new_data, numbers);
        } else {
            printf("n/a");
        }
    } else {
        printf("n/a");
    }
    return 0;
}

int sum_numbers(int *buffer, int length) {
    int sum = 0;
    for (int *p = buffer; p - buffer < length; p++) {
        if (*p % 2 == 0) {
            sum += *p;
        }
    }
    return sum;
}

int input(int *a, int *length) {
    int r = SUCCESS;
    char c;
    if (scanf("%d", length) != 1 || *length > NMAX || *length <= 0) {
        r = ERROR_INPUT;
    } else {
        for (int *p = a; p - a < *length; p++)
            if (scanf("%d%c", p, &c) != 2 || (c != ' ' && c != '\n')) {
                r = ERROR_INPUT;
                break;
            }
    }
    return r;
}

void output(int *a, int length) {
    for (int *p = a; p - a < length; p++) {
        if (p - a != length - 1)
            printf("%d ", *p);
        else
            printf("%d", *p);
    }
}

int find_numbers(int *buffer, int length, int number, int *numbers) {
    int *i = numbers;
    int count = 0;
    for (int *p = buffer; p - buffer < length; p++) {
        if (*p != 0 && number % *p == 0) {
            *(i + count) = *p;
            count++;
        }
    }
    return count;
}