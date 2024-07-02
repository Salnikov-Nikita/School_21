#ifndef LEVELS_H
#define LEVELS_H

#include <stdio.h>

#include "table.h"

struct level {
    int level;  // aka id
    int cell_count;
    int protected;
};

int open_levels(struct table *table, const char *path);

int parse_level(struct level *level, const char *str);
int display_level(const struct level *level, char *str, size_t n);

#endif