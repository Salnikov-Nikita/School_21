#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>

const int WIDTH = 80;
const int HEIGHT = 25;
const int SCORE_GOAL = 21;

// const int WIDTH = 16;
// const int HEIGHT = 7;
// const int SCORE_GOAL = 2;

const int PADDLE_SIZE = 3;
const int PADDLE1_X = 2;
const int PADDLE2_X = WIDTH - 1 - 2;

int move_paddle(int paddle_y, int offset) {
    paddle_y += offset;
    if (paddle_y < 0) {
        paddle_y = 0;
    } else if (paddle_y + PADDLE_SIZE > HEIGHT) {
        paddle_y = HEIGHT - PADDLE_SIZE;
    }
    return paddle_y;
}

bool ball_hits_paddle(int paddle_x, int paddle_y, int ball_x, int ball_y, int ball_vx, int ball_vy) {
    int check_y;
    if (ball_x == paddle_x) {
        check_y = ball_y;
    } else if (ball_x + ball_vx == paddle_x) {
        check_y = ball_y + ball_vy;
    } else {
        return false;
    }
    return check_y >= paddle_y && check_y < paddle_y + PADDLE_SIZE;
}

void score_display(int score1, int score2) {
    int score_width = (WIDTH - 3) / 2;
    for (int x = 0; x < WIDTH; ++x) {
        mvaddch(1, x, '=');
        mvaddch(HEIGHT + 2, x, '=');
    }
    mvprintw(0, 0, "%*d | %*d", score_width, score1, -score_width, score2);
    for (int x = 0; x < WIDTH; ++x) {
        mvaddch(1, x, '=');
        mvaddch(HEIGHT + 2, x, '=');
    }
}

void paddle_display(int paddle_x, int paddle_y, bool show) {
    char ch = show ? '|' : ' ';
    for (int i = 0; i < PADDLE_SIZE; ++i) {
        mvaddch(2 + paddle_y + i, paddle_x, ch);
    }
}

void ball_display(int ball_x, int ball_y, bool show) {
    char ch = show ? 'O' : ' ';
    mvaddch(2 + ball_y, ball_x, ch);
}

int play_game(void) {
    int score1 = 0, score2 = 0;

    while (score1 < SCORE_GOAL && score2 < SCORE_GOAL) {
        int round = score1 + score2;
        int paddle1_y = (HEIGHT - PADDLE_SIZE) / 2;
        int paddle2_y = (HEIGHT - PADDLE_SIZE) / 2;
        int ball_x = WIDTH / 2, ball_y = HEIGHT / 2;
        int ball_vx = -1, ball_vy = -1;
        if (round % 2 != 0) {
            ball_vx = 1;
            ball_vy = 1;
        }

        clear();
        score_display(score1, score2);
        paddle_display(PADDLE1_X, paddle1_y, true);
        paddle_display(PADDLE2_X, paddle2_y, true);
        ball_display(ball_x, ball_y, true);

        while (ball_x >= 0 && ball_x < WIDTH) {
            refresh();
            int command = getch();

            switch (command) {
                case 'a':
                case 'z': {
                    paddle_display(PADDLE1_X, paddle1_y, false);
                    paddle1_y = move_paddle(paddle1_y, command == 'a' ? -1 : 1);
                    paddle_display(PADDLE1_X, paddle1_y, true);
                    break;
                }
                case 'k':
                case 'm': {
                    paddle_display(PADDLE2_X, paddle2_y, false);
                    paddle2_y = move_paddle(paddle2_y, command == 'k' ? -1 : 1);
                    paddle_display(PADDLE2_X, paddle2_y, true);
                    break;
                }
            }

            ball_display(ball_x, ball_y, false);
            if (ball_y == 0 && ball_vy < 0) {
                ball_vy = 1;
            } else if (ball_y == HEIGHT - 1 && ball_vy > 0) {
                ball_vy = -1;
            }
            if (ball_hits_paddle(PADDLE1_X, paddle1_y, ball_x, ball_y, ball_vx, ball_vy)) {
                ball_vx = 1;
            } else if (ball_hits_paddle(PADDLE2_X, paddle2_y, ball_x, ball_y, ball_vx, ball_vy)) {
                ball_vx = -1;
            }
            ball_x += ball_vx;
            ball_y += ball_vy;
            ball_display(ball_x, ball_y, true);
        }

        if (ball_x < 0) {
            score2 += 1;
        } else if (ball_x >= WIDTH) {
            score1 += 1;
        }
    }
    clear();
    refresh();

    if (score1 >= SCORE_GOAL) {
        return 1;
    } else {
        return 2;
    }
}

int main(void) {
    initscr();
    cbreak();
    noecho();
    timeout(100);
    curs_set(0);

    int winner = play_game();

    endwin();

    if (winner != 0) {
        printf("Player %d won, congratulations!", winner);
    }
}