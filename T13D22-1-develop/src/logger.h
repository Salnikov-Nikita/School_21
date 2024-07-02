#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#include "log_levels.h"

FILE *log_init(char *filename);

int logcat(FILE *log_file, char *message, log_level level);
int logcat_fmt(FILE *log_file, log_level level, char *fmt, ...);

int log_close(FILE *log_file);

#endif