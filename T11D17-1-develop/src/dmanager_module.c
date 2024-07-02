#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(struct door *doors);
void init_door(struct door *doors);
void sort(struct door *doors, int n);
void output(struct door *doors, int n);
void close_doors(struct door *doors, int n);

int main() {
    struct door doors[DOORS_COUNT];

    initialize_doors(doors);
    sort(doors, DOORS_COUNT);
    close_doors(doors, DOORS_COUNT);
    output(doors, DOORS_COUNT);
    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % MAX_ID_SEED;
        doors[i].status = rand() % 2;
    }
}

void sort(struct door *doors, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (doors[i].id > doors[j].id) {
                int tmp = doors[i].id;
                doors[i].id = doors[j].id;
                doors[j].id = tmp;
            }
}

void output(struct door *doors, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d, %d", doors[i].id, doors[i].status);
        if (i + 1 != n) printf("\n");
    }
}

void close_doors(struct door *doors, int n) {
    for (int i = 0; i < n; i++) {
        doors[i].status = 0;
    }
}