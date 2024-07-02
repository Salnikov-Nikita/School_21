#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define M 80
#define N 25

#define LIVE '#'
#define DEAD ' '

char **create_array(int n, int m);
int input_array(char **array, int n, int m);
void game_loop(char **prev, int n, int m, char **next);
void game_draw(char **array, int n, int m);
void game_step(char **prev, int n, int m, char **next);
char get_wrapping(char **array, int n, int m, int i, int j);

int main(void) {
    char **prev = create_array(N, M);
    char **next = create_array(N, M);

    if (input_array(prev, N, M)) {
        freopen("/dev/tty", "r", stdin);
        game_loop(prev, N, M, next);
    } else {
        printf("n/a");
    }

    free(next);
    free(prev);
}

char **create_array(int n, int m) {
    char **array = (char **)malloc(n * sizeof(char *) + n * m * sizeof(char));
    char *a = (char *)(array + n);
    for (int i = 0; i < n; i++) {
        array[i] = &a[i * m];
    }
    return array;
}

int input_array(char **array, int n, int m) {
    int result = 1;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int ch = getchar();
            if (ch == LIVE || ch == DEAD) {
                array[i][j] = ch;
            } else {
                result = 0;
                break;
            }
        }
        if (!result) {
            break;
        }
        if (i < n - 1 && getchar() != '\n') {
            result = 0;
            break;
        }
    }

    if (result && getchar() != EOF) {
        result = 0;
    }

    return result;
}

void game_loop(char **prev, int n, int m, char **next) {
    int t = 128;

    initscr();
    cbreak();
    noecho();
    timeout(t);
    curs_set(0);

    clear();
    for (;;) {
        game_draw(prev, n, m);
        refresh();
        int ch = getch();
        if (ch == 'a' && t > 1) {
            t /= 2;
            timeout(t);
        } else if (ch == 'z' && t < 1024) {
            t *= 2;
            timeout(t);
        } else if (ch == 'q') {
            break;
        }
        game_step(prev, n, m, next);
        char **tmp = prev;
        prev = next;
        next = tmp;
    }
    clear();
    refresh();

    endwin();
}

void game_step(char **prev, int n, int m, char **next) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int k = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (get_wrapping(prev, n, m, i + di, j + dj) == LIVE) {
                        k += 1;
                    }
                }
            }
            char state = DEAD;
            if (prev[i][j] == LIVE) {
                if (k - 1 == 2 || k - 1 == 3) {
                    state = LIVE;
                }
            } else {
                if (k == 3) {
                    state = LIVE;
                }
            }
            next[i][j] = state;
        }
    }
}

void game_draw(char **array, int n, int m) {
    for (int i = 0; i < n; ++i) {
        mvaddnstr(i, 0, array[i], m);
    }
}

char get_wrapping(char **array, int n, int m, int i, int j) {
    i %= n;
    j %= m;
    if (i < 0) i += n;
    if (j < 0) j += m;
    return array[i][j];
}