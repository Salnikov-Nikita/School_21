#ifndef DATABASE_H
#define DATABASE_H

#include "levels.h"
#include "modules.h"
#include "status_events.h"
#include "table.h"

struct database {
    struct table modules;
    struct table levels;
    struct table status_events;
};

enum db_table {
    db_modules = 1,
    db_levels = 2,
    db_status_events = 3,
};

union db_entry {
    struct module module;
    struct level level;
    struct status_event status_event;
};

int open_database(struct database *db, const char *base_path);
int close_database(struct database *db);

int db_entry_id(enum db_table table, const union db_entry *entry);

int parse_db_entry(enum db_table table, union db_entry *entry, const char *str);
int display_db_entry(enum db_table table, const union db_entry *entry, char *str, size_t n);

int db_table_length(struct database *db, enum db_table table);

int read_db_entry(struct database *db, enum db_table table, int index, union db_entry *entry);
int write_db_entry(struct database *db, enum db_table table, int index, const union db_entry *entry);

int find_db_entry(struct database *db, enum db_table table, int id);

int select_db_entry(struct database *db, enum db_table table, int id, union db_entry *entry);
int insert_db_entry(struct database *db, enum db_table table, union db_entry *entry);
int update_db_entry(struct database *db, enum db_table table, const union db_entry *entry);
int delete_db_entry(struct database *db, enum db_table table, int id);

#endif