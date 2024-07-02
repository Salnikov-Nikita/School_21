#include "modules.h"

int open_modules(struct table *table, const char *path) {
    return open_table(table, path, sizeof(struct module));
}

int parse_module(struct module *module, const char *str) {
    return sscanf(str, "%d \"%29[^\"]\"%d%d%d", &module->id, module->name, &module->level, &module->cell,
                  &module->deleted) == 5;
}

int display_module(const struct module *module, char *str, size_t n) {
    return snprintf(str, n, "%d \"%s\" %d %d %d", module->id, module->name, module->level, module->cell,
                    module->deleted) < (int)n;
}
