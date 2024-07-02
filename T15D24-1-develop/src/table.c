#include "table.h"

#include <stdlib.h>
#include <unistd.h>

int open_table(struct table *table, const char *path, size_t entry_size) {
    int ok = path != NULL && entry_size > 0;
    FILE *file = ok ? fopen(path, "r+b") : NULL;
    int len = 0;
    char *temp = NULL;
    if (file != NULL) {
        ok = ok && fseek(file, 0, SEEK_END) == 0;
        long size = ftell(file);
        ok = ok && size >= 0 && size % entry_size == 0;
        len = ok ? size / entry_size : 0;
        temp = ok ? malloc(entry_size) : NULL;
        ok = ok && temp != NULL;
        if (!ok) {
            fclose(file);
            if (temp != NULL) free(temp);
            file = NULL;
            temp = NULL;
        }
    } else {
        ok = 0;
    }
    table->file = file;
    table->entry_size = entry_size;
    table->len = len;
    table->next_id = -1;
    table->temp = temp;
    return ok;
}

int close_table(struct table *table) {
    int ok = table->file != NULL ? fclose(table->file) == 0 : 0;
    if (table->temp != NULL) free(table->temp);
    table->file = NULL;
    table->temp = NULL;
    return ok;
}

int len_table(struct table *table) { return table->len; }

int resize_table(struct table *table, int len) {
    int ok = len >= 0;
    ok = ok && ftruncate(fileno(table->file), len * (long)table->entry_size) == 0;
    // ok = ok && freopen(NULL, "r+b", table->file) != NULL;
    if (ok) table->len = len;
    return ok;
}

int read_entry(struct table *table, int index, void *entry) {
    int ok = index >= 0 && index < table->len;
    ok = ok && fseek(table->file, index * (long)table->entry_size, SEEK_SET) == 0;
    ok = ok && fread(entry, table->entry_size, 1, table->file) == 1;
    return ok;
}

int write_entry(struct table *table, int index, const void *entry) {
    int ok = index >= 0 && index <= table->len;
    ok = ok && fseek(table->file, index * (long)table->entry_size, SEEK_SET) == 0;
    ok = ok && fwrite(entry, table->entry_size, 1, table->file) == 1;
    if (ok && index == table->len) table->len += 1;
    ok = ok && fflush(table->file) == 0;
    return ok;
}

int find_entry(struct table *table, int id) {
    int ok = table->len >= 1;
    ok = ok && fseek(table->file, 0, SEEK_SET) == 0;
    int found = -1;
    if (ok) {
        for (int i = 0; ok && found < 0 && i < table->len; i++) {
            ok = ok && fread(table->temp, table->entry_size, 1, table->file) == 1;
            if (ok && *(int *)table->temp == id) {
                found = i;
            }
        }
    }
    return ok ? found : -1;
}

int compute_next_id(struct table *table) {
    int ok = fseek(table->file, 0, SEEK_SET) == 0;
    int max_id = -1;
    if (ok) {
        for (int i = 0; i < table->len; i++) {
            ok = ok && fread(table->temp, table->entry_size, 1, table->file) == 1;
            int id = ok ? *(int *)table->temp : max_id;
            if (id > max_id) max_id = id;
        }
    }
    if (ok) table->next_id = max_id + 1;
    return ok;
}

int select_entry(struct table *table, int id, void *entry) {
    int index = find_entry(table, id);
    return index >= 0 && read_entry(table, index, entry);
}

int update_entry(struct table *table, const void *entry) {
    int id = *(int *)entry;
    int index = find_entry(table, id);
    return index >= 0 && write_entry(table, index, entry);
}

int insert_entry(struct table *table, void *entry) {
    int ok = 1;
    int id = *(int *)entry;
    if (id < 0) {
        if (table->next_id < 0) {
            ok = ok && compute_next_id(table);
        }
        if (ok) {
            id = table->next_id++;
            *(int *)entry = id;
        }
    }
    return ok && write_entry(table, table->len, entry);
}

int delete_entry(struct table *table, int id) {
    int index = find_entry(table, id);
    int ok = index >= 0;
    if (ok && index != table->len - 1) {
        ok = ok && read_entry(table, table->len - 1, table->temp);
        ok = ok && write_entry(table, index, table->temp);
    }
    ok = ok && resize_table(table, table->len - 1);
    return ok;
}
