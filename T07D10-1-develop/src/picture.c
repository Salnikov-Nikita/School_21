#include <stdio.h>

#define N 15
#define M 13

void transform(int *buf, int **matr, int n, int m);
void make_picture(int **picture, int n, int m);
void reset_picture(int **picture, int n, int m);
void show_picture(int **picture, int n, int m);

int main() {
    int picture_data[N][M];
    int *picture[N];
    transform((int *)picture_data, picture, N, M);

    make_picture(picture, N, M);

    show_picture(picture, N, M);
}

void make_picture(int **picture, int n, int m) {
    int frame_w[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int frame_h[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int tree_trunk[] = {7, 7, 7, 7};
    int tree_foliage[] = {3, 3, 3, 3};
    int sun_data[6][5] = {{0, 6, 6, 6, 6}, {0, 0, 6, 6, 6}, {0, 0, 6, 6, 6},
                          {0, 6, 0, 0, 6}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    reset_picture(picture, n, m);

    int length_tree_foliage = sizeof(tree_foliage) / sizeof(tree_foliage[0]);

    for (int i = 0; i < length_tree_foliage; i++) {
        picture[2 + i][3] = tree_foliage[i];
        picture[2 + i][4] = tree_foliage[i];
        picture[3][2 + i] = tree_foliage[i];
        picture[4][2 + i] = tree_foliage[i];
    }

    int length_tree_trunk = sizeof(tree_trunk) / sizeof(tree_trunk[0]);

    for (int i = 0; i < length_tree_trunk; i++) {
        picture[6 + i][3] = tree_trunk[i];
        picture[6 + i][4] = tree_trunk[i];
        picture[10][2 + i] = tree_trunk[i];
    }

    int length_frame_w = sizeof(frame_w) / sizeof(frame_w[0]);

    for (int i = 0; i < length_frame_w; i++) {
        picture[0][i] = frame_w[i];
        picture[7][i] = frame_w[i];
        picture[14][i] = frame_w[i];
    }

    int length_frame_h = sizeof(frame_h) / sizeof(frame_h[0]);

    for (int i = 0; i < length_frame_h; i++) {
        picture[i][0] = frame_h[i];
        picture[i][6] = frame_h[i];
        picture[i][12] = frame_h[i];
    }

    int height_sun_data = sizeof(sun_data) / sizeof(sun_data[0]);
    int width_sun_data = sizeof(sun_data[0]) / sizeof(sun_data[0][0]);

    for (int i = 0; i < height_sun_data; i++) {
        for (int j = 0; j < width_sun_data; j++) {
            picture[1 + i][7 + j] = sun_data[i][j];
        }
    }
}

void reset_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            picture[i][j] = 0;
        }
    }
}

void transform(int *buf, int **matr, int n, int m) {
    for (int i = 0; i < n; i++) {
        matr[i] = buf + i * m;
    }
}

void show_picture(int **picture, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", picture[i][j]);
            if (j < m - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
}