#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculation.h"
#include "draw.h"
#include "mystack.h"

int main() {
    char **graph = calloc_matrix(HEIGHT, WIDTH + 1);
    struct st *operations = NULL;
    char input_string[80];
    int token_string[80];
    int output_string[80];
    fgets(input_string, 80, stdin);
    int tokens_len = parse_tokens(input_string, token_string);
    int len_result =
        tokens_len > 0 ? parsing_in_polish_notation(operations, token_string, tokens_len, output_string) : -1;
    if (len_result > 0) {
        HEAD head;
        init(&head);
        init_graph(graph, HEIGHT, WIDTH);
        add_func_for_graph(graph, HEIGHT, WIDTH, output_string, &head, len_result);
        draw_graph(graph, HEIGHT, WIDTH);
        free_matrix(graph, HEIGHT);
    } else {
        printf("SYNTAX ERROR");
    }
    return 0;
}
