#include <stdio.h>
#include <string.h>

#include "entry.h"

#define LINE_MAX 100

int read_line(char *line, size_t size);

int sort_entries(FILE *file);
int compare_entries(const struct entry *a, const struct entry *b);

int main() {
    char path[LINE_MAX];
    int ok = read_line(path, LINE_MAX);
    FILE *file = ok ? open_entry_file(path) : NULL;
    ok = ok && file != NULL;
    int type;
    ok = ok && scanf("%d", &type) == 1;
    if (ok) {
        if (type == 0) {
            ok = ok && display_entries(file);
        } else if (type == 1) {
            ok = ok && sort_entries(file);
            ok = ok && display_entries(file);
        } else if (type == 2) {
            struct entry entry;
            ok = ok && input_entry(&entry);
            ok = ok && append_entry(file, &entry);
            ok = ok && sort_entries(file);
            ok = ok && display_entries(file);
        } else {
            ok = 0;
        }
    }
    if (file != NULL) {
        ok = ok && close_entry_file(file);
    }
    if (!ok) {
        printf("n/a");
    }
    return 0;
}

int read_line(char *line, size_t size) {
    int ok = fgets(line, size, stdin) != NULL;
    if (ok) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = 0;
        } else {
            ok = 0;
        }
    } else {
        line[0] = '\0';
    }
    return ok;
}

int sort_entries(FILE *file) {
    int ok = 1;
    int n = num_entries(file);
    ok = ok && n > 0;
    if (ok) {
        for (int i = 0; i < n; ++i) {
            struct entry entry, min_entry;
            ok = ok && read_entry(file, i, &min_entry);
            int min_index = i;
            for (int j = i + 1; j < n; ++j) {
                ok = ok && read_entry(file, j, &entry);
                if (ok && compare_entries(&entry, &min_entry) < 0) {
                    min_index = j;
                    min_entry = entry;
                }
            }
            if (min_index != i) {
                ok = ok && read_entry(file, i, &entry);
                ok = ok && write_entry(file, i, &min_entry);
                ok = ok && write_entry(file, min_index, &entry);
            }
        }
    }
    return ok;
}

int compare_entries(const struct entry *a, const struct entry *b) {
    int cmp = 0;
    if (a == NULL || b == NULL) {
        cmp = (a != NULL) - (b != NULL);
    } else if (a->year != b->year) {
        cmp = a->year - b->year;
    } else if (a->month != b->month) {
        cmp = a->month - b->month;
    } else if (a->day != b->day) {
        cmp = a->day - b->day;
    } else if (a->hour != b->hour) {
        cmp = a->hour - b->hour;
    } else if (a->minute != b->minute) {
        cmp = a->minute - b->minute;
    } else if (a->second != b->second) {
        cmp = a->second - b->second;
    } else if (a->state != b->state) {
        cmp = a->state - b->state;
    } else if (a->code != b->code) {
        cmp = a->code - b->code;
    }
    return cmp;
}
