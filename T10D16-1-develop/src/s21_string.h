#ifndef STR_21_LIB_H
#define STR_21_LIB_H

#include <stdlib.h>

size_t s21_strlen(const char *string);
int s21_strcmp(const char *string_1, const char *string_2);
char *s21_strcpy(char *string_build, const char *string_source);
char *s21_strcat(char *string_build, const char *string_add);
char *s21_strchr(const char *string, char c);
char *s21_strstr(const char *string_source, const char *string_find);
char *s21_strtok(char *string, const char *delim);

#endif