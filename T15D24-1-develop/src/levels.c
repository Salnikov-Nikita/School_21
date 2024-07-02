#include "levels.h"

int open_levels(struct table *table, const char *path) {
    return open_table(table, path, sizeof(struct level));
}

int parse_level(struct level *level, const char *str) {
    return sscanf(str, "%d%d%d", &level->level, &level->cell_count, &level->protected) == 3;
}

int display_level(const struct level *level, char *str, size_t n) {
    return snprintf(str, n, "%d %d %d", level->level, level->cell_count, level->protected) < (int)n;
}
