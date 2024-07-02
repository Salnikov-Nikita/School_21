#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

size_t s21_strlen(const char *string) {
    size_t len = 0;
    if (string != NULL) {
        for (; *string; string++) len++;
    }
    return len;
}

int s21_strcmp(const char *string_1, const char *string_2) {
    int cmp = 0;
    if (string_1 != NULL && string_2 != NULL) {
        for (; *string_1 && *string_1 == *string_2; string_1++, string_2++) {
        }
        cmp = *string_1 - *string_2;
    } else {
        cmp = (string_1 != NULL) - (string_2 != NULL);
    }
    return cmp;
}

char *s21_strcpy(char *string_build, const char *string_source) {
    if (string_build != NULL && string_source != NULL) {
        for (int i = 0; (string_build[i] = string_source[i]) != '\0'; i++) {
        }
    }
    return string_source != NULL ? string_build : NULL;
}

char *s21_strcat(char *string_build, const char *string_add) {
    if (string_build != NULL && string_add != NULL) {
        s21_strcpy(string_build + s21_strlen(string_build), string_add);
    }
    return string_add != NULL ? string_build : NULL;
}

char *s21_strchr(const char *string, char c) {
    if (string != NULL) {
        for (; *string && *string != c; string++) {
        }
    }
    return string != NULL && *string ? (char *)string : NULL;
}

char *s21_strstr(const char *string_source, const char *string_find) {
    const char *string_find_ptr = NULL, *string_source_ptr = NULL;
    const char *out = NULL;
    if (string_source != NULL && string_find != NULL) {
        for (;;) {
            int trigger_out = 1;

            string_find_ptr = string_find;
            string_source_ptr = string_source;

            while (*string_find_ptr && *string_source_ptr) {
                trigger_out = trigger_out && (*string_find_ptr == *string_source_ptr);
                string_find_ptr++;
                string_source_ptr++;
            }

            if (trigger_out && !*string_find_ptr) {
                out = string_source;
                break;
            } else if (!*string_source) {
                break;
            }
            string_source++;
        }
    }
    return (char *)out;
}

char *s21_strtok(char *string, const char *delim) {
    // статическая переменная сохраняет значение между вызовами функции
    static char *saved = NULL;
    // "проверка ошибок" - delim не должен быть NULL
    if (!delim) {
        // сбрасываем все на NULL, чтобы остаток функции не пытался что-то где-то искать
        string = NULL;
        saved = NULL;
    }
    // нам передали NULL - продолжаем работу с сохраненной строкой
    if (!string) {
        string = saved;
    }
    // еще раз проверка, если в прошлый раз уже вернули последнее слово, то saved тоже был NULL
    if (string) {
        // пропускаем "пробелы" в начале
        while (*string && s21_strchr(delim, *string)) {
            string++;
        }
        if (!*string) {
            // слов больше нет, будем возвращать NULL
            string = NULL;
            saved = NULL;
        } else {
            // нашли начало слова, теперь ищем "пробел" после слова
            saved = string;
            while (*saved && !s21_strchr(delim, *saved)) {
                saved++;
            }
            if (*saved) {
                // нашли конец слова, делим строку в этом месте, запоминаем остаток строки
                *saved = 0;
                saved++;
            }
        }
    }
    // возвращаем указатель на начало слова
    return string;
}