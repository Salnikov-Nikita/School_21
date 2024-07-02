#include "list.h"

#include <stdio.h>

#define SUCCESS 1
#define FAIL 0

int list_test_1(void);
int list_test_2(void);
int list_test_3(void);

int main() {
    printf("list_test_1 - %s\n", list_test_1() == SUCCESS ? "SUCCESS" : "FAIL");
    printf("list_test_2 - %s\n", list_test_2() == SUCCESS ? "SUCCESS" : "FAIL");
    printf("list_test_3 - %s\n", list_test_3() == SUCCESS ? "SUCCESS" : "FAIL");
}

// список с одним элементом
int list_test_1(void) {
    struct door door;
    struct node *root;
    struct node *elem;
    int ok = 1;

    door.id = 42;
    door.status = 1;
    root = init(&door);

    elem = find_door(42, root);
    ok = ok && elem != NULL && elem->door.id == 42 && elem->door.status == 1;

    elem = find_door(100, root);
    ok = ok && elem == NULL;

    destroy(root);

    return ok ? SUCCESS : FAIL;
}

// список с несколькими элементами
int list_test_2(void) {
    struct door door;
    struct node *root;
    struct node *elem;
    int ok = 1;

    door.status = 0;

    door.id = 1;
    root = init(&door);
    door.id = 10;
    elem = add_door(root, &door);
    door.id = 20;
    add_door(elem, &door);
    door.id = 5;
    add_door(root, &door);
    // 1, 5, 10, 20

    elem = find_door(1, root);
    ok = ok && elem == root;
    elem = find_door(5, root);
    ok = ok && elem == root->next;
    elem = find_door(10, root);
    ok = ok && elem == root->next->next;
    elem = find_door(20, root);
    ok = ok && elem == root->next->next->next;

    elem = find_door(42, root);
    ok = ok && elem == NULL;

    door.id = 15;
    add_door(find_door(10, root), &door);
    // 1, 5, 10, 15, 20

    elem = find_door(15, root);
    ok = ok && elem == root->next->next->next;

    destroy(root);

    return ok ? SUCCESS : FAIL;
}

// удаление элементов
int list_test_3(void) {
    struct door door;
    struct node *root;
    struct node *elem;
    int ok = 1;

    door.status = 0;

    door.id = 1;
    root = init(&door);
    door.id = 4;
    add_door(root, &door);
    door.id = 3;
    add_door(root, &door);
    door.id = 2;
    add_door(root, &door);
    // 1, 2, 3, 4

    root = remove_door(find_door(3, root), root);
    elem = find_door(3, root);
    ok = ok && elem == NULL;
    elem = find_door(4, root);
    ok = ok && elem != NULL && elem->door.id == 4;

    root = remove_door(root, root);
    elem = find_door(1, root);
    ok = ok && elem == NULL;
    elem = find_door(2, root);
    ok = ok && elem != NULL && elem->door.id == 2;
    elem = find_door(4, root);
    ok = ok && elem != NULL && elem->door.id == 4;

    destroy(root);

    return ok ? SUCCESS : FAIL;
}
