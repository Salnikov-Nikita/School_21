#include <stdio.h>
#define N 10
#define SUCCESS 1
#define ERROR_INPUT 0

int input(int *a);
void output(int *a);
void quick_sort(int *a, int first, int last);
void copy_data(int *a, int *b);
void siftDown(int *a, int first, int last);
void heapSort(int *a);

int main(void) {
    int data_1[N];
    int check = input(data_1);
    if (check) {
        int data_2[N];
        copy_data(data_1, data_2);
        quick_sort(data_1, 0, N - 1);
        output(data_1);
        printf("\n");
        heapSort(data_2);
        output(data_2);
    } else {
        printf("n/a");
    }
    return 0;
}

int input(int *a) {
    int r = SUCCESS;
    char c;
    for (int *p = a; p - a < N; p++)
        if (scanf("%d%c", p, &c) != 2 || (c != ' ' && c != '\n')) {
            r = ERROR_INPUT;
            break;
        }

    return r;
}

void output(int *a) {
    for (int *p = a; p - a < N; p++) {
        if (p - a != N - 1)
            printf("%d ", *p);
        else
            printf("%d", *p);
    }
}

/*
algorithm quicksort(A, low, high) is
    if low < high then
        p:= partition(A, low, high)
        quicksort(A, low, p - 1)
        quicksort(A, p, high)
*/

void quick_sort(int *a, int first, int last) {  // quick_sort
    if (first < last) {
        int left = first, right = last, middle = *(a + (left + right) / 2);
        do {
            while (*(a + left) < middle) left++;
            while (*(a + right) > middle) right--;
            if (left <= right) {
                int tmp = *(a + left);
                *(a + left) = *(a + right);
                *(a + right) = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quick_sort(a, first, right);
        quick_sort(a, left, last);
    }
}

void siftDown(int *a, int first, int last) {
    int maxChild;  // индекс максимального потомка
    int done = 0;  // флаг того, что куча сформирована
    // Пока не дошли до последнего ряда
    while ((first * 2 <= last) && (!done)) {
        if (first * 2 == last)     // если мы в последнем ряду,
            maxChild = first * 2;  // запоминаем левый потомок
        // иначе запоминаем больший потомок из двух
        else if (*(a + first * 2) > *(a + first * 2 + 1))
            maxChild = first * 2;
        else
            maxChild = first * 2 + 1;
        // если элемент вершины меньше максимального потомка
        if (*(a + first) < *(a + maxChild)) {
            int temp = *(a + first);  // меняем их местами
            *(a + first) = *(a + maxChild);
            *(a + maxChild) = temp;
            first = maxChild;
        } else         // иначе
            done = 1;  // пирамида сформирована
    }
}
// Функция сортировки на куче
void heapSort(int *a) {
    // Формируем нижний ряд пирамиды
    for (int i = (N / 2); i >= 0; i--) siftDown(a, i, N - 1);
    // Просеиваем через пирамиду остальные элементы
    for (int i = N - 1; i >= 1; i--) {
        int temp = *a;
        *a = *(a + i);
        *(a + i) = temp;
        siftDown(a, 0, i - 1);
    }
}

void copy_data(int *a, int *b) {
    for (int *p = a, *q = b; p - a < N; p++, q++) *q = *p;
}