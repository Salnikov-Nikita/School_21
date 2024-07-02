#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>

struct table {
    FILE *file;
    size_t entry_size;
    int len;
    int next_id;
    char *temp;
};

int open_table(struct table *table, const char *path, size_t entry_size);
int close_table(struct table *table);

int len_table(struct table *table);
int resize_table(struct table *table, int len);

int read_entry(struct table *table, int index, void *entry);
int write_entry(struct table *table, int index, const void *entry);

// эти функции требуют, что структура entry начиналась с поля int id

int find_entry(struct table *table, int id);

int select_entry(struct table *table, int id, void *entry);
int update_entry(struct table *table, const void *entry);
int insert_entry(struct table *table, void *entry);
int delete_entry(struct table *table, int id);

#endif