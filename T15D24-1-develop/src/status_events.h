#ifndef STATUS_EVENTS_H
#define STATUS_EVENTS_H

#include "table.h"

struct status_event {
    int id;
    int module_id;
    int status;
    char date[10 + 1];  // dd.mm.yyyy\0
    char time[8 + 1];   // hh:mm:ss\0
};

int open_status_events(struct table *table, const char *path);

int parse_status_event(struct status_event *status_event, const char *str);
int display_status_event(const struct status_event *status_event, char *str, size_t n);

#endif