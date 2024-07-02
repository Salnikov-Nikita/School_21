#include <stdio.h>
#include <string.h>

#include "entry.h"

#define LINE_MAX 100

int read_line(char *line, size_t size);

int find_entry(FILE *file, int year, int month, int day, struct entry *entry);

int main() {
    char path[LINE_MAX];
    int ok = read_line(path, LINE_MAX);
    FILE *file = ok ? open_entry_file(path) : NULL;
    ok = ok && file != NULL;
    int year, month, day;
    ok = ok && scanf("%d.%d.%d", &day, &month, &year) == 3;
    struct entry entry;
    ok = ok && find_entry(file, year, month, day, &entry);
    if (ok) {
        printf("%d", entry.code);
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

int find_entry(FILE *file, int year, int month, int day, struct entry *entry) {
    int ok = 1;
    int n = num_entries(file);
    ok = ok && n > 0;
    int found = 0;
    for (int i = 0; ok && !found && i < n; ++i) {
        ok = ok && read_entry(file, i, entry);
        if (ok && entry->year == year && entry->month == month && entry->day == day) {
            found = 1;
        }
    }
    return ok && found;
}
