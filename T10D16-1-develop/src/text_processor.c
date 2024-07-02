#include <stdio.h>

#include "s21_string.h"

int read_line(char *line, size_t size);
void format_text(char *string, int width);

int main(int argc, char **argv) {
    int ok = 1;
    ok = ok && argc == 2 && s21_strcmp(argv[1], "-w") == 0;
    char line[128];
    int width;
    ok = ok && read_line(line, sizeof(line)) && sscanf(line, "%d", &width) == 1 && width >= 2;
    ok = ok && read_line(line, sizeof(line)) && s21_strlen(line) <= 100;
    if (ok) {
        format_text(line, width);
    } else {
        printf("n/a");
    }
    return 0;
}

int read_line(char *line, size_t size) {
    int ok = fgets(line, size, stdin) != NULL;
    if (ok) {
        char *str = s21_strchr(line, '\n');
        if (str != NULL) {
            *str = 0;
        } else {
            ok = 0;
        }
    }
    return ok;
}

void format_text(char *string, int width) {
    const char *delim = " ";
    int remaining = width;
    char saved_char = '\0';
    const char *word = s21_strtok(string, delim);
    while (word) {
        int len = (int)s21_strlen(word);
        if (len <= remaining) {
            // слово входит в текущую строку
            if (saved_char) {
                printf("%c", saved_char);
            }
            printf("%s", word);
            remaining -= len + 1;
            saved_char = ' ';
            if (remaining <= 0) {
                // строка закончилась
                remaining = width;
                saved_char = '\n';
            }
            // выведено все слово
            word += len;
        } else if (len > width && remaining >= 2) {
            // слово в принципе не может войти в строку целиком - переносим
            if (saved_char) {
                printf("%c", saved_char);
            }
            printf("%.*s-", remaining - 1, word);
            word += remaining - 1;
            remaining = width;
            saved_char = '\n';
        } else {
            // слово не входит в эту строку, но войдет в следующую
            remaining = width;
            saved_char = '\n';
        }
        // если текущее слово было дописано целиком, переходим на следующее слово
        if (!*word) {
            word = s21_strtok(NULL, delim);
        }
    }
}