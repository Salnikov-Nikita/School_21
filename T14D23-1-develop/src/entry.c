#include "entry.h"

#include <unistd.h>

FILE *open_entry_file(const char *path) {
    FILE *file = fopen(path, "r+b");
    if (file != NULL) {
        int ok = 1;
        ok = ok && fseek(file, 0, SEEK_END) == 0;
        long size = ok ? ftell(file) : -1;
        ok = ok && size >= 0 && size % sizeof(struct entry) == 0;
        if (!ok) {
            fclose(file);
            file = NULL;
        }
    }
    return file;
}

int num_entries(FILE *file) {
    int ok = file != NULL;
    ok = ok && fseek(file, 0, SEEK_END) == 0;
    long size = ftell(file);
    ok = ok && size >= 0;
    return ok ? (int)(size / sizeof(struct entry)) : -1;
}

int resize_entry_file(FILE *file, int n) {
    int ok = file != NULL && n >= 0;
    ok = ok && ftruncate(fileno(file), n * (long)sizeof(struct entry)) == 0;
    // ok = ok && freopen(NULL, "r+b", file) != NULL;
    return ok;
}

int read_entry(FILE *file, int index, struct entry *entry) {
    int ok = file != NULL && entry != NULL;
    ok = ok && fseek(file, index * (long)sizeof(struct entry), SEEK_SET) == 0;
    ok = ok && fread(entry, sizeof(struct entry), 1, file) == 1;
    return ok;
}

int write_entry(FILE *file, int index, const struct entry *entry) {
    int ok = file != NULL && entry != NULL;
    ok = ok && fseek(file, index * (long)sizeof(struct entry), SEEK_SET) == 0;
    ok = ok && fwrite(entry, sizeof(struct entry), 1, file) == 1;
    ok = ok && fflush(file) == 0;
    return ok;
}

int append_entry(FILE *file, const struct entry *entry) {
    int ok = file != NULL && entry != NULL;
    ok = ok && fseek(file, 0, SEEK_END) == 0;
    ok = ok && fwrite(entry, sizeof(struct entry), 1, file) == 1;
    ok = ok && fflush(file) == 0;
    return ok;
}

int close_entry_file(FILE *file) { return file != NULL ? fclose(file) == 0 : 0; }

int input_entry(struct entry *entry) {
    int ok = entry != NULL;
    ok = ok && scanf("%d%d%d%d%d%d%d%d", &entry->year, &entry->month, &entry->day, &entry->hour,
                     &entry->minute, &entry->second, &entry->state, &entry->code) == 8;
    ok = ok && entry->year >= 0 && entry->year <= 9999;
    ok = ok && entry->month >= 1 && entry->month <= 12;
    ok = ok && entry->day >= 1 && entry->day <= 31;
    ok = ok && entry->hour >= 0 && entry->hour <= 23;
    ok = ok && entry->minute >= 0 && entry->minute <= 59;
    ok = ok && entry->second >= 0 && entry->second <= 59;
    ok = ok && entry->state >= 0 && entry->state <= 1;
    return ok;
}

int display_entry(const struct entry *entry) {
    int ok = entry != NULL;
    if (ok) {
        printf("%d %d %d %d %d %d %d %d", entry->year, entry->month, entry->day, entry->hour, entry->minute,
               entry->second, entry->state, entry->code);
    }
    return ok;
}

int display_entries(FILE *file) {
    int ok = 1;
    int n = num_entries(file);
    ok = ok && n > 0;
    if (ok) {
        for (int i = 0; i < n; ++i) {
            struct entry entry;
            ok = ok && read_entry(file, i, &entry);
            if (ok) {
                ok = ok && display_entry(&entry);
                if (ok && i < n - 1) putchar('\n');
            }
        }
    }
    return ok;
}
