#include <stdio.h>
#include <string.h>

#include "entry.h"

#define LINE_MAX 100

int read_line(char *line, size_t size);

int erase_entries(FILE *file, int year1, int month1, int day1, int year2, int month2, int day2);

int compare_dates(int year1, int month1, int day1, int year2, int month2, int day2);

int main() {
    char path[LINE_MAX];
    int ok = read_line(path, LINE_MAX);
    FILE *file = ok ? open_entry_file(path) : NULL;
    ok = ok && file != NULL;
    int year1, month1, day1, year2, month2, day2;
    ok = ok && scanf("%d.%d.%d", &day1, &month1, &year1) == 3;
    ok = ok && scanf("%d.%d.%d", &day2, &month2, &year2) == 3;
    ok = ok && erase_entries(file, year1, month1, day1, year2, month2, day2);
    ok = ok && display_entries(file);
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

int erase_entries(FILE *file, int year1, int month1, int day1, int year2, int month2, int day2) {
    int ok = 1;
    int n = num_entries(file);
    ok = ok && n > 0;
    int written = 0;
    for (int i = 0; ok && i < n; ++i) {
        struct entry entry;
        ok = ok && read_entry(file, i, &entry);
        int erasing = ok;
        erasing = erasing && compare_dates(entry.year, entry.month, entry.day, year1, month1, day1) >= 0;
        erasing = erasing && compare_dates(entry.year, entry.month, entry.day, year2, month2, day2) <= 0;
        if (!erasing) {
            if (i > written) {
                ok = ok && write_entry(file, written, &entry);
            }
            written++;
        }
    }
    if (written < n) {
        ok = ok && resize_entry_file(file, written);
    }
    return ok;
}

int compare_dates(int year1, int month1, int day1, int year2, int month2, int day2) {
    int cmp = 0;
    if (year1 != year2) {
        cmp = year1 - year2;
    } else if (month1 != month2) {
        cmp = month1 - month2;
    } else if (day1 != day2) {
        cmp = day1 - day2;
    }
    return cmp;
}