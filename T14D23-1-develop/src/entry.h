#ifndef ENTRY_H
#define ENTRY_H

#include <stdio.h>

struct entry {
    int year, month, day, hour, minute, second, state, code;
};

FILE *open_entry_file(const char *path);
int num_entries(FILE *file);
int resize_entry_file(FILE *file, int n);
int read_entry(FILE *file, int index, struct entry *entry);
int write_entry(FILE *file, int index, const struct entry *entry);
int append_entry(FILE *file, const struct entry *entry);
int close_entry_file(FILE *file);

int input_entry(struct entry *entry);
int display_entry(const struct entry *entry);
int display_entries(FILE *file);

#endif