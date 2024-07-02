#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logger.h"

#define LINE_MAX 100

int read_line(char *line, size_t size);
int display_file(const char *path, FILE *log_file);
int append_to_file(const char *path, const char *line, FILE *log_file);

int encrypt_directory(const char *path, int key, FILE *log_file);
int ends_with(const char *path, const char *ext);
int clear_file(const char *path, FILE *log_file);
int encrypt_file(const char *path, int key, FILE *log_file);
void encrypt_data(char *data, size_t n, int key);

int main() {
    FILE *log_file = NULL;
#ifdef USE_LOGGER
    log_file = log_init("cipher.log");
#endif
    logcat(log_file, "program started", info);
    int type = 0;
    char line[LINE_MAX];
    char path[LINE_MAX];
    path[0] = '\0';
    for (;;) {
        int ok = read_line(line, LINE_MAX);
        ok = ok && sscanf(line, "%d", &type) == 1;
        if (!ok) {
            type = 0;
        }
        if (type == -1) {
            break;
        } else if (type == 1) {
            ok = read_line(path, LINE_MAX);
            ok = ok && display_file(path, log_file);
        } else if (type == 2) {
            ok = read_line(line, LINE_MAX);
            ok = ok && path[0] != '\0' && append_to_file(path, line, log_file);
            ok = ok && display_file(path, log_file);
        } else if (type == 3) {
            int key;
            ok = read_line(line, LINE_MAX);
            ok = ok && sscanf(line, "%d", &key) == 1;
            ok = ok && read_line(line, LINE_MAX);
            ok = ok && encrypt_directory(line, key, log_file);
            if (ok) {
                printf("encryption complete");
            }
        } else {
            ok = 0;
        }
        printf(ok ? "\n" : "n/a\n");
    }
    logcat(log_file, "program finished", info);
    log_close(log_file);
    return 0;
}

int read_line(char *line, size_t size) {
    int ok = fgets(line, size, stdin) != NULL;
    if (ok) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = 0;
        } else {
            ok = 0;
        }
    } else {
        line[0] = '\0';
    }
    return ok;
}

int display_file(const char *path, FILE *log_file) {
    logcat_fmt(log_file, info, "displaying file %s", path);
    FILE *f = fopen(path, "r");
    int ok = f != NULL;
    int empty = 1;
    if (ok) {
        char buf[1024];
        while (ok && !feof(f)) {
            size_t n = fread(buf, 1, sizeof buf, f);
            ok = ok && !ferror(f);
            if (n > 0) {
                empty = 0;
                fwrite(buf, 1, n, stdout);
            }
        }
    }
    if (f != NULL) {
        fclose(f);
    }
    if (!ok) {
        logcat_fmt(log_file, error, "failed displaying file %s", path);
    }
    return ok && !empty;
}

int append_to_file(const char *path, const char *line, FILE *log_file) {
    logcat_fmt(log_file, info, "appending to file %s", path);
    FILE *f = fopen(
        path, "r+");  // mode = "a" не подходит, так как в случае, когда файл не существует, "a" создает его
    int ok = f != NULL;
    ok = ok && fseek(f, 0, SEEK_END) == 0;
    ok = ok && fputs(line, f) != EOF;
    if (f != NULL) {
        fclose(f);
    }
    if (!ok) {
        logcat_fmt(log_file, error, "failed appending to file %s", path);
    }
    return ok;
}

int encrypt_directory(const char *path, int key, FILE *log_file) {
    logcat_fmt(log_file, info, "encrypting directory %s with key %d", path, key);
    size_t npath = strlen(path);
    DIR *d = opendir(path);
    int ok = d != NULL;
    struct dirent *entry;
    if (ok) {
        while (ok && (entry = readdir(d)) != NULL) {
            logcat_fmt(log_file, trace, "considering file %s/%s", path, entry->d_name);
            if (ends_with(entry->d_name, ".h") || ends_with(entry->d_name, ".c")) {
                size_t nname = strlen(entry->d_name);
                size_t nfilepath = npath + 1 + nname;
                char *filepath = malloc(nfilepath + 1);
                if (filepath != NULL) {
                    snprintf(filepath, nfilepath + 1, "%s/%s", path, entry->d_name);
                    if (entry->d_name[nname - 1] == 'h') {
                        ok = ok && clear_file(filepath, log_file);
                    } else {
                        ok = ok && encrypt_file(filepath, key, log_file);
                    }
                    free(filepath);
                } else {
                    ok = 0;
                }
            }
        }
        closedir(d);
    }
    if (!ok) {
        logcat_fmt(log_file, error, "failed encrypting directory %s", path);
    }
    return ok;
}

int ends_with(const char *path, const char *ext) {
    size_t npath = strlen(path), next = strlen(ext);
    return npath >= next && memcmp(path + (npath - next), ext, next) == 0;
}

int clear_file(const char *path, FILE *log_file) {
    logcat_fmt(log_file, info, "clearing file %s", path);
    FILE *f = fopen(path, "w");
    int ok = f != NULL;
    if (f != NULL) {
        fclose(f);
    }
    if (!ok) {
        logcat_fmt(log_file, error, "failed clearing file %s", path);
    }
    return ok;
}

int encrypt_file(const char *path, int key, FILE *log_file) {
    logcat_fmt(log_file, info, "encrypting file %s with key %d", path, key);
    FILE *f = fopen(path, "r+b");
    int ok = f != NULL;
    if (ok) {
        char buf[1024];
        int done = 0;
        while (ok && !done) {
            size_t n = fread(buf, 1, sizeof buf, f);
            done = feof(f);
            ok = ok && !ferror(f);
            encrypt_data(buf, n, key);
            ok = ok && fseek(f, -(long)n, SEEK_CUR) == 0;
            if (ok) {
                size_t m = fwrite(buf, 1, n, f);
                ok = ok && m == n && fseek(f, 0, SEEK_CUR) == 0;
            }
        }
    }
    if (f != NULL) {
        fclose(f);
    }
    if (!ok) {
        logcat_fmt(log_file, error, "failed encrypting file %s", path);
    }
    return ok;
}

void encrypt_data(char *data, size_t n, int key) {
    for (size_t i = 0; i < n; i++) {
        data[i] = (char)(unsigned char)(data[i] + key);
    }
}
