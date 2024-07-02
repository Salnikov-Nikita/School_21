#ifndef MODULES_H
#define MODULES_H

#include "table.h"

struct module {
    int id;
    char name[30];
    int level;
    int cell;
    int deleted;
};

int open_modules(struct table *table, const char *path);

int parse_module(struct module *module, const char *str);
int display_module(const struct module *module, char *str, size_t n);

#endif