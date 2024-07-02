#include <stdio.h>
#include <string.h>

#include "mystack.h"
// функция обработки функций
int check_token(char **input_str, char *token) {
    int n = strlen(token);
    int ok = 0;
    if (strncmp(*input_str, token, n) == 0) {
        char *token_end = *input_str + n;
        if (*token_end < 'a' || *token_end > 'z') {
            ok = 1;
            *input_str = token_end;
        }
    }
    return ok;
}

int parse_tokens(char *input_str, int *output_str) {
    int point = 0;
    while (*input_str != '\0') {
        if (strchr(" \t\n", *input_str) != NULL) {  // обработка пробелов
            input_str++;
        } else if (strchr("+-*/()", *input_str) != NULL) {  // обработка операторов
            output_str[point++] = *input_str++;
        } else if (*input_str >= '0' && *input_str <= '9') {  // обработка чисел
            int value = 0;
            do {
                value *= 10;
                value += *input_str - '0';
                input_str++;
            } while (*input_str >= '0' && *input_str <= '9');
            output_str[point++] = -value;
        } else if (check_token(&input_str, "x")) {  // обработка функций
            output_str[point++] = 'x';
        } else if (check_token(&input_str, "sin")) {
            output_str[point++] = 's';
        } else if (check_token(&input_str, "cos")) {
            output_str[point++] = 'c';
        } else if (check_token(&input_str, "tan")) {
            output_str[point++] = 't';
        } else if (check_token(&input_str, "ctg")) {
            output_str[point++] = 'g';
        } else if (check_token(&input_str, "sqrt")) {
            output_str[point++] = 'q';
        } else if (check_token(&input_str, "ln")) {
            output_str[point++] = 'l';
        } else {
            point = -1;
            break;
        }
    }
    return point;
}

int parsing_in_polish_notation(struct st *operations, int *input_str, int input_len, int *output_str) {
    int point = 0, unar_flag = 1, ok = 1;
    for (int i = 0; i < input_len; i++) {
        int token = input_str[i];
        if (unar_flag && token == '-') token = 'n';

        if (token == ')') {
            ok = ok && !unar_flag;
            while (operations != NULL && (operations->c) != '(') output_str[point++] = delete (&operations);
            ok = ok && operations != NULL;
            delete (&operations);
            unar_flag = 0;
        }

        if (token == 'x' || token <= 0) {
            ok = ok && unar_flag;
            output_str[point++] = token;
            unar_flag = 0;
        }

        int p = priority(token);

        if (p > 0 && token != '(') {
            if (p == 4)
                ok = ok && unar_flag;
            else
                ok = ok && !unar_flag;

            if (operations == NULL) {
                operations = push(operations, token);
            } else if (priority(operations->c) < p)
                operations = push(operations, token);
            else {
                while ((operations != NULL) && (priority(operations->c) >= p))
                    output_str[point++] = delete(&operations);
                operations = push(operations, token);
            }
            unar_flag = 1;
        } else if (token == '(') {
            ok = ok && unar_flag;
            operations = push(operations, '(');
            unar_flag = 1;
        }
    }
    ok = ok && !unar_flag;
    while (operations != NULL) output_str[point++] = delete (&operations);

    return ok ? point : -1;
}