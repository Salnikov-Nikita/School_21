#include <stdio.h>

const int WIDTH = 80;
const int HEIGHT = 25;
const int SCORE_GOAL = 21;

// const int WIDTH = 10;
// const int HEIGHT = 7;
// const int SCORE_GOAL = 2;

const int PADDLE_SIZE = 3;
const int PADDLE1_X = 0;
const int PADDLE2_X = WIDTH - 1;

int move_paddle(int paddle_y, int offset) {
    paddle_y += offset;
    if (paddle_y < 0) {
        paddle_y = 0;
    } else if (paddle_y + PADDLE_SIZE > HEIGHT) {
        paddle_y = HEIGHT - PADDLE_SIZE;
    }
    return paddle_y;
}

int ball_hits_paddle(int paddle_x, int paddle_y, int ball_x, int ball_y, int ball_vx, int ball_vy) {
    int check_y;
    if (ball_x == paddle_x) {
        check_y = ball_y;
    } else if (ball_x + ball_vx == paddle_x) {
        check_y = ball_y + ball_vy;
    } else {
        return 0;
    }
    return check_y >= paddle_y && check_y < paddle_y + PADDLE_SIZE ? 1 : 0;
}

void score_display(int score1, int score2) {
    int score_width = (WIDTH - 3) / 2;
    // printf("==========\n");
    printf("================================================================================\n");
    printf("%*d | %*d\n", score_width, score1, -score_width, score2);
    // printf("==========\n");
    printf("================================================================================\n");
}

void game_display(int paddle1_y, int paddle2_y, int ball_x, int ball_y) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == ball_x && y == ball_y) {
                putchar('*');
            } else if (x == PADDLE1_X && y >= paddle1_y && y < paddle1_y + PADDLE_SIZE) {
                putchar('|');
            } else if (x == PADDLE2_X && y >= paddle2_y && y < paddle2_y + PADDLE_SIZE) {
                putchar('|');
            } else {
                putchar(' ');
            }
        }
        putchar('\n');
    }
    // printf("==========\n");
    printf("================================================================================\n");
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

        while (ball_x >= 0 && ball_x < WIDTH) {
            score_display(score1, score2);
            game_display(paddle1_y, paddle2_y, ball_x, ball_y);

            int command;
            do {
                command = getchar();
            } while (command == '\n');
            if (command == EOF) {
                return 0;
            }

            switch (command) {
                case 'a':
                    paddle1_y = move_paddle(paddle1_y, -1);
                    break;
                case 'z':
                    paddle1_y = move_paddle(paddle1_y, 1);
                    break;
                case 'k':
                    paddle2_y = move_paddle(paddle2_y, -1);
                    break;
                case 'm':
                    paddle2_y = move_paddle(paddle2_y, 1);
                    break;
            }

            if (ball_y == 0 && ball_vy < 0) {
                ball_vy = 1;
            } else if (ball_y == HEIGHT - 1 && ball_vy > 0) {
                ball_vy = -1;
            }
            if (ball_hits_paddle(PADDLE1_X, paddle1_y, ball_x, ball_y, ball_vx, ball_vy) == 1) {
                ball_vx = 1;
            } else if (ball_hits_paddle(PADDLE2_X, paddle2_y, ball_x, ball_y, ball_vx, ball_vy) == 1) {
                ball_vx = -1;
            }
            ball_x += ball_vx;
            ball_y += ball_vy;
        }

        if (ball_x < 0) {
            score2 += 1;
        } else if (ball_x >= WIDTH) {
            score1 += 1;
        }
    }

    if (score1 >= SCORE_GOAL) {
        return 1;
    } else {
        return 2;
    }
}

int main(void) {
    int winner = play_game();
    if (winner != 0) {
        printf("Player %d won, congratulations!", winner);
    }
}