#include "list.h"

#include <stdlib.h>

struct node *init(struct door *door) {
    struct node *root = door != NULL ? malloc(sizeof(struct node)) : NULL;
    if (root != NULL) {
        root->door = *door;
        root->next = NULL;
    }
    return root;
}

struct node *add_door(struct node *elem, struct door *door) {
    struct node *node = NULL;
    if (elem != NULL) {
        node = init(door);
        if (node != NULL) {
            node->next = elem->next;
            elem->next = node;
        }
    }
    return node;
}

struct node *find_door(int door_id, struct node *root) {
    struct node *node = root;
    while (node != NULL && node->door.id != door_id) {
        node = node->next;
    }
    return node;
}

struct node *remove_door(struct node *elem, struct node *root) {
    if (elem != NULL && root != NULL) {
        if (elem == root) {
            root = root->next;
            free(elem);
        } else {
            struct node *prev = root;
            while (prev != NULL && prev->next != elem) {
                prev = prev->next;
            }
            if (prev != NULL) {
                prev->next = elem->next;
                free(elem);
            }
        }
    }
    return root;
}

void destroy(struct node *root) {
    while (root != NULL) {
        struct node *next = root->next;
        free(root);
        root = next;
    }
}
