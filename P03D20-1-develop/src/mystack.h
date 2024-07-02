#ifndef MYSTACK_H_
#define MYSTACK_H_

struct st {
    char c;
    struct st *next;
};
struct st *push(struct st *, char);
char delete(struct st **);
int priority(char);

int parsing_in_polish_notation(struct st *operations, int *input_str, int input_len, int *output_str);
int parse_tokens(char *input_str, int *output_str);

#endif  // MYSTACK_H_