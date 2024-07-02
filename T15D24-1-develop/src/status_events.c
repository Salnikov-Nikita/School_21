#include "status_events.h"

int open_status_events(struct table *table, const char *path) {
    return open_table(table, path, sizeof(struct status_event));
}

int parse_status_event(struct status_event *status_event, const char *str) {
    return sscanf(str, "%d%d%d%10s%8s", &status_event->id, &status_event->module_id, &status_event->status,
                  status_event->date, status_event->time) == 5;
}

int display_status_event(const struct status_event *status_event, char *str, size_t n) {
    return snprintf(str, n, "%d %d %d %s %s", status_event->id, status_event->module_id, status_event->status,
                    status_event->date, status_event->time) < (int)n;
}
