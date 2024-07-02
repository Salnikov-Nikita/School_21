#include "shared.h"

#include <time.h>

struct stack *get_active_additional_modules(struct database *db) {
    struct stack *stack = stack_init();
    int len = db_table_length(db, db_modules);
    for (int i = 0; i < len; ++i) {
        struct module module;
        int ok = read_entry(&db->modules, i, &module);
        if (ok && module.id != 0 && !module.deleted && get_module_status(db, module.id) == 1) {
            stack_push(stack, module.id);
        }
    }
    return stack;
}

int get_module_status(struct database *db, int module_id) {
    int len = db_table_length(db, db_status_events);
    int status = -1;
    int last_time[7] = {0, 0, 0, 0, 0, 0, -1};  // year, month, day, hour, minute, second, id
    for (int i = 0; i < len; ++i) {
        struct status_event status_event;
        int ok = read_entry(&db->status_events, i, &status_event);
        if (ok && status_event.module_id == module_id) {
            int event_time[7];
            ok = ok &&
                 sscanf(status_event.date, "%d.%d.%d", &event_time[2], &event_time[1], &event_time[0]) == 3;
            ok = ok &&
                 sscanf(status_event.time, "%d:%d:%d", &event_time[3], &event_time[4], &event_time[5]) == 3;
            event_time[6] = ok ? status_event.id : -1;
            if (ok) {
                int cmp = 0;
                for (int j = 0; j < 7 && cmp == 0; ++j) {
                    cmp = event_time[j] - last_time[j];
                }
                if (cmp > 0) {
                    status = status_event.status;
                    for (int j = 0; j < 7; ++j) {
                        last_time[j] = event_time[j];
                    }
                }
            }
        }
    }
    return status;
}

int set_module_status(struct database *db, int module_id, int status) {
    struct status_event status_event = {-1, module_id, status, "", ""};
    time_t now = time(NULL);
    strftime(status_event.date, 10 + 1, "%d.%m.%Y", localtime(&now));
    strftime(status_event.time, 8 + 1, "%H:%M:%S", localtime(&now));
    return insert_entry(&db->status_events, &status_event);
}

int set_module_deleted(struct database *db, int module_id, int deleted) {
    struct module module;
    int ok = select_entry(&db->modules, module_id, &module);
    if (ok) {
        module.deleted = deleted;
        ok = update_entry(&db->modules, &module);
    }
    return ok;
}

int move_module_to_cell(struct database *db, int module_id, int level, int cell) {
    struct module module;
    int ok = select_entry(&db->modules, module_id, &module);
    if (ok) {
        module.level = level;
        module.cell = cell;
        ok = update_entry(&db->modules, &module);
    }
    return ok;
}

struct stack *get_modules_in_cell(struct database *db, int level, int cell) {
    struct stack *stack = stack_init();
    int len = db_table_length(db, db_modules);
    for (int i = 0; i < len; ++i) {
        struct module module;
        int ok = read_entry(&db->modules, i, &module);
        if (ok && !module.deleted && module.level == level && module.cell == cell) {
            stack_push(stack, module.id);
        }
    }
    return stack;
}

int set_level_protected(struct database *db, int level_no, int protected) {
    struct level level;
    int ok = select_entry(&db->levels, level_no, &level);
    if (ok) {
        level.protected = protected;
        ok = update_entry(&db->levels, &level);
    }
    return ok;
}
