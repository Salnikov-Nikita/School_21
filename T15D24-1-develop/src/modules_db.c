#include <stdio.h>
#include <string.h>

#include "database.h"
#include "shared.h"

#define SELECT_ALL_ID -999999999

int process_action(struct database *db);

int read_line(char *line, size_t size);
int read_int(int dflt);

void print_stack(struct stack *stack);

int main(void) {
    struct database db;
    int ok = open_database(&db, "materials");
    if (!ok) {
        ok = open_database(&db, "../materials");
    }
    if (ok) {
        int done = 0;
        while (!done) {
            done = process_action(&db);
        }
        close_database(&db);
    } else {
        printf("Error opening database");
    }
    return 0;
}

int process_action(struct database *db) {
    int done = 0;
    printf(
        "Please choose one operation:\n"
        "  1. SELECT\n"
        "  2. INSERT\n"
        "  3. UPDATE\n"
        "  4. DELETE\n"
        "  5. Display AI status\n"
        "  6. Deactivate AI\n"
        "  0. Exit\n");
    int choice = read_int(-1);
    enum db_table table = 0;
    if (choice >= 1 && choice <= 4) {
        printf(
            "Please choose a table:\n"
            "  1. Modules\n"
            "  2. Levels\n"
            "  3. Status events\n"
            "  0. Cancel\n");
        table = read_int(0);
    }
    if (choice == 0) {
        done = 1;
    } else if (choice == 1 && table != 0) {
        printf("Enter id, or leave empty to display all:\n");
        int id = read_int(SELECT_ALL_ID);
        if (id != SELECT_ALL_ID) {
            union db_entry entry;
            int ok = select_db_entry(db, table, id, &entry);
            char buf[128];
            ok = ok && display_db_entry(table, &entry, buf, sizeof(buf));
            if (ok) {
                puts(buf);
            } else {
                printf("Error selecting entry\n");
            }
        } else {
            int len = db_table_length(db, table);
            union db_entry entry;
            char buf[128];
            int ok = 1;
            for (int i = 0; ok && i < len; ++i) {
                if (i > 0 && i % 20 == 0) {
                    printf("Continue? 1 - yes, 0 - no\n");
                    if (!read_int(1)) break;
                }
                ok = ok && read_db_entry(db, table, i, &entry);
                ok = ok && display_db_entry(table, &entry, buf, sizeof(buf));
                if (ok) puts(buf);
            }
            if (!ok) printf("Error selecting entries\n");
        }
    } else if (choice == 2 && table != 0) {
        printf("Enter details (enter negative id for autoincrement):\n");
        char line[128];
        int ok = read_line(line, sizeof(line));
        union db_entry entry;
        ok = ok && parse_db_entry(table, &entry, line);
        ok = ok && insert_db_entry(db, table, &entry);
        if (ok) {
            printf("Entry inserted, id = %d\n", db_entry_id(table, &entry));
        } else {
            printf("Error inserting entry\n");
        }
    } else if (choice == 3 && table != 0) {
        printf("Enter details:\n");
        char line[128];
        int ok = read_line(line, sizeof(line));
        union db_entry entry;
        ok = ok && parse_db_entry(table, &entry, line);
        ok = ok && update_db_entry(db, table, &entry);
        printf(ok ? "Entry updated\n" : "Error updating entry\n");
    } else if (choice == 4 && table != 0) {
        printf("Enter id:\n");
        int id = read_int(-1);
        int ok = delete_db_entry(db, table, id);
        printf(ok ? "Entry deleted\n" : "Error deleting entry\n");
    } else if (choice == 5 || choice == 6) {
        int world_saved = 1;
        int do_actions = choice == 6;
        struct stack *active_modules = get_active_additional_modules(db);
        printf("Active additional modules: ");
        print_stack(active_modules);
        putchar('\n');
        world_saved = world_saved && active_modules->next == NULL;
        if (do_actions) {
            for (struct stack *node = active_modules->next; node != NULL; node = node->next) {
                int ok;
                printf("Deactivating module %d: ", node->value);
                ok = set_module_status(db, node->value, 0);
                printf("%s\n", ok ? "ok" : "error");
                printf("Deleting module %d: ", node->value);
                ok = set_module_deleted(db, node->value, 1);
                printf("%s\n", ok ? "ok" : "error");
            }
        }
        stack_destroy(active_modules);
        int main_status = get_module_status(db, 0);
        printf("Main module status: %d\n", main_status);
        world_saved = world_saved && main_status == 20;
        if (do_actions && main_status != 20) {
            printf("Switching main module to protected mode: ");
            int ok = 1;
            ok = ok && set_module_status(db, 0, 0);
            ok = ok && set_module_status(db, 0, 1);
            ok = ok && set_module_status(db, 0, 20);
            printf("%s\n", ok ? "ok" : "error");
        }
        struct stack *modules_in_cell = get_modules_in_cell(db, 1, 1);
        printf("Modules in cell (1, 1): ");
        print_stack(modules_in_cell);
        putchar('\n');
        world_saved = world_saved && (modules_in_cell->next == NULL || modules_in_cell->next->next == NULL);
        union db_entry entry;
        int main_in_cell = 0;
        if (select_db_entry(db, db_modules, 0, &entry)) {
            main_in_cell = entry.module.level == 1 && entry.module.cell == 1;
        }
        printf("Main module %s (1, 1)\n", main_in_cell ? "in" : "not in");
        world_saved = world_saved && main_in_cell;
        if (do_actions) {
            for (struct stack *node = modules_in_cell->next; node != NULL; node = node->next) {
                if (node->value != 0) {
                    printf("Moving module %d away from (1, 1): ", node->value);
                    int ok = move_module_to_cell(db, node->value, 1, 2);
                    printf("%s\n", ok ? "ok" : "error");
                }
            }
            if (!main_in_cell) {
                printf("Moving main module to (1, 1): ");
                int ok = move_module_to_cell(db, 0, 1, 1);
                printf("%s\n", ok ? "ok" : "error");
            }
        }
        stack_destroy(modules_in_cell);
        int level_protected = 0;
        if (select_db_entry(db, db_levels, 1, &entry)) {
            level_protected = entry.level.protected;
        }
        printf("Level 1 %s protected\n", level_protected ? "is" : "is not");
        world_saved = world_saved && level_protected;
        if (do_actions && !level_protected) {
            printf("Setting protection flag for level 1: ");
            int ok = set_level_protected(db, 1, 1);
            printf("%s\n", ok ? "ok" : "error");
        }
        if (do_actions) {
            printf("AI deactivation complete, please check AI status again\n");
        } else {
            printf("World status: %s\n", world_saved ? "SAVED" : "IN DANGER");
        }
    }
    putchar('\n');
    return done;
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

int read_int(int dflt) {
    char line[32];
    int ok = read_line(line, sizeof(line));
    int value;
    ok = ok && sscanf(line, "%d", &value) == 1;
    return ok ? value : dflt;
}

void print_stack(struct stack *stack) {
    int first = 1;
    for (struct stack *node = stack->next; node != NULL; node = node->next) {
        if (!first) putchar(',');
        first = 0;
        printf(" %d", node->value);
    }
    if (first) printf("none");
}
