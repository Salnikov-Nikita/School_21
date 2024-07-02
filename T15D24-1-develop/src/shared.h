#ifndef SHARED_H
#define SHARED_H

#include "database.h"
#include "stack.h"

struct stack *get_active_additional_modules(struct database *db);
int get_module_status(struct database *db, int module_id);
int set_module_status(struct database *db, int module_id, int status);
int set_module_deleted(struct database *db, int module_id, int deleted);
struct stack *get_modules_in_cell(struct database *db, int level, int cell);
int move_module_to_cell(struct database *db, int module_id, int level, int cell);
int set_level_protected(struct database *db, int level_no, int protected);

#endif