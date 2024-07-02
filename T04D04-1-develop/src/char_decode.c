#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
 
int fail() {
    puts("n/a");
    exit(0);
}
 
 
int fromhex(unsigned char ch) {
    if ('0' <= ch && ch <= '9') {
        return ch-'0';
    } else if ('A' <= ch && ch <= 'F') {
        return ch-'A'+10;
    } else {
        return fail();
    }
}
 
unsigned char tohex(int v) {
    return v < 10 ? v+'0' : v-10+'A';
}
 
 
int read_space() {
    int ch = getchar();
    if (ch == EOF || ch == '\n') return 0;
    if (ch != ' ') fail();
    return 1;
}
 
void read_word(unsigned char *word, int n) {
    for (int i = 0; i < n; ++i) {
        int ch = getchar();
        if (ch == EOF || ch == '\n') fail();
        word[i] = ch;
    }
}
 
 
void encode(void) {
    int n = 0;
    unsigned char word[1];
    do {
        read_word(word, 1);
        int ch = word[0];
        if (n) putchar(' ');
        putchar(tohex(ch/16));
        putchar(tohex(ch%16));
        n += 1;
    } while (read_space());
}
 
void decode(void) {
    int n = 0;
    unsigned char word[2];
    do {
        read_word(word, 2);
        int ch = fromhex(word[0])*16 + fromhex(word[1]);
        if (n) putchar(' ');
        putchar(ch);
        n += 1;
    } while (read_space());
}
 
 
int main(int argc, char **argv) {
    if (argc != 2) {
        fail();
    } else if (strcmp(argv[1], "0") == 0) {
        encode();
    } else if (strcmp(argv[1], "1") == 0) {
        decode();
    } else {
        fail();
    }
}
 
