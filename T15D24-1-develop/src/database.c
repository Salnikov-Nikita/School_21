#include "database.h"

#include <stdlib.h>
#include <string.h>

int open_database(struct database *db, const char *base_path) {
    size_t npath = strlen(base_path);
    char *buf = malloc(npath + 32);
    int ok = buf != NULL;
    if (buf != NULL) {
        sprintf(buf, "%s/master_modules.db", base_path);
        int ok_modules = open_modules(&db->modules, buf);
        sprintf(buf, "%s/master_levels.db", base_path);
        int ok_levels = open_levels(&db->levels, buf);
        sprintf(buf, "%s/master_status_events.db", base_path);
        int ok_status_events = open_status_events(&db->status_events, buf);
        ok = ok && ok_modules && ok_levels && ok_status_events;
        free(buf);
        if (!ok) {
            if (ok_modules) close_table(&db->modules);
            if (ok_levels) close_table(&db->levels);
            if (ok_status_events) close_table(&db->status_events);
        }
    }
    return ok;
}

int close_database(struct database *db) {
    int ok_modules = close_table(&db->modules);
    int ok_levels = close_table(&db->levels);
    int ok_status_events = close_table(&db->status_events);
    return ok_modules && ok_levels && ok_status_events;
}

int db_entry_id(enum db_table table, const union db_entry *entry) {
    int res = -1;
    if (table == db_modules) {
        res = entry->module.id;
    } else if (table == db_levels) {
        res = entry->level.level;
    } else if (table == db_status_events) {
        res = entry->status_event.id;
    }
    return res;
}

int parse_db_entry(enum db_table table, union db_entry *entry, const char *str) {
    int ok = 0;
    if (table == db_modules) {
        ok = parse_module(&entry->module, str);
    } else if (table == db_levels) {
        ok = parse_level(&entry->level, str);
    } else if (table == db_status_events) {
        ok = parse_status_event(&entry->status_event, str);
    }
    return ok;
}

int display_db_entry(enum db_table table, const union db_entry *entry, char *str, size_t n) {
    int ok = 0;
    if (table == db_modules) {
        ok = display_module(&entry->module, str, n);
    } else if (table == db_levels) {
        ok = display_level(&entry->level, str, n);
    } else if (table == db_status_events) {
        ok = display_status_event(&entry->status_event, str, n);
    }
    return ok;
}

int db_table_length(struct database *db, enum db_table table) {
    int res = -1;
    if (table == db_modules) {
        res = len_table(&db->modules);
    } else if (table == db_levels) {
        res = len_table(&db->levels);
    } else if (table == db_status_events) {
        res = len_table(&db->status_events);
    }
    return res;
}

int read_db_entry(struct database *db, enum db_table table, int index, union db_entry *entry) {
    int ok = 0;
    if (table == db_modules) {
        ok = read_entry(&db->modules, index, &entry->module);
    } else if (table == db_levels) {
        ok = read_entry(&db->levels, index, &entry->level);
    } else if (table == db_status_events) {
        ok = read_entry(&db->status_events, index, &entry->status_event);
    }
    return ok;
}

int write_db_entry(struct database *db, enum db_table table, int index, const union db_entry *entry) {
    int ok = 0;
    if (table == db_modules) {
        ok = write_entry(&db->modules, index, &entry->module);
    } else if (table == db_levels) {
        ok = write_entry(&db->levels, index, &entry->level);
    } else if (table == db_status_events) {
        ok = write_entry(&db->status_events, index, &entry->status_event);
    }
    return ok;
}

int find_db_entry(struct database *db, enum db_table table, int id) {
    int res = -1;
    if (table == db_modules) {
        res = find_entry(&db->modules, id);
    } else if (table == db_levels) {
        res = find_entry(&db->levels, id);
    } else if (table == db_status_events) {
        res = find_entry(&db->status_events, id);
    }
    return res;
}

int select_db_entry(struct database *db, enum db_table table, int id, union db_entry *entry) {
    int ok = 0;
    if (table == db_modules) {
        ok = select_entry(&db->modules, id, &entry->module);
    } else if (table == db_levels) {
        ok = select_entry(&db->levels, id, &entry->level);
    } else if (table == db_status_events) {
        ok = select_entry(&db->status_events, id, &entry->status_event);
    }
    return ok;
}

int insert_db_entry(struct database *db, enum db_table table, union db_entry *entry) {
    int ok = 0;
    if (table == db_modules) {
        ok = insert_entry(&db->modules, &entry->module);
    } else if (table == db_levels) {
        ok = insert_entry(&db->levels, &entry->level);
    } else if (table == db_status_events) {
        ok = insert_entry(&db->status_events, &entry->status_event);
    }
    return ok;
}

int update_db_entry(struct database *db, enum db_table table, const union db_entry *entry) {
    int ok = 0;
    if (table == db_modules) {
        ok = update_entry(&db->modules, &entry->module);
    } else if (table == db_levels) {
        ok = update_entry(&db->levels, &entry->level);
    } else if (table == db_status_events) {
        ok = update_entry(&db->status_events, &entry->status_event);
    }
    return ok;
}

int delete_db_entry(struct database *db, enum db_table table, int id) {
    int ok = 0;
    if (table == db_modules) {
        ok = delete_entry(&db->modules, id);
    } else if (table == db_levels) {
        ok = delete_entry(&db->levels, id);
    } else if (table == db_status_events) {
        ok = delete_entry(&db->status_events, id);
    }
    return ok;
}
