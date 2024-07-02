#include "logger.h"

#include <stdarg.h>
#include <stdlib.h>
#include <time.h>

FILE *log_init(char *filename) { return fopen(filename, "a"); }

int logcat(FILE *log_file, char *message, log_level level) {
    int ok = 0;
    if (log_file != NULL) {
        time_t now = time(NULL);
        char time_buf[16];
        strftime(time_buf, sizeof time_buf, "%H:%M:%S", localtime(&now));
        const char *level_string = "DEBUG";
        if (level == trace) {
            level_string = "TRACE";
        } else if (level == info) {
            level_string = "INFO";
        } else if (level == warning) {
            level_string = "WARNING";
        } else if (level == error) {
            level_string = "ERROR";
        }
        ok = fprintf(log_file, "[%s] %s %s\n", level_string, time_buf, message) >= 0;
    }
    return ok;
}

int logcat_fmt(FILE *log_file, log_level level, char *fmt, ...) {
    int ok = 0;
    if (log_file != NULL) {
        va_list args1;
        va_start(args1, fmt);
        va_list args2;
        va_copy(args2, args1);
        size_t sz = vsnprintf(NULL, 0, fmt, args1) + 1;
        char *message = malloc(sz);
        va_end(args1);
        if (message != NULL) {
            vsnprintf(message, sz, fmt, args2);
            ok = logcat(log_file, message, level);
            free(message);
        } else {
            ok = 0;
        }
        va_end(args2);
    }
    return ok;
}

int log_close(FILE *log_file) {
    int ok = 0;
    if (log_file != NULL) {
        ok = fclose(log_file) == 0;
    }
    return ok;
}
