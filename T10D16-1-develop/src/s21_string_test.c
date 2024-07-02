#include "s21_string.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef QUEST
#define QUEST 7
#endif

void s21_strlen_test(const char *string, size_t expected_len) {
    printf("%s\n", string ? string : "NULL");
    size_t len = s21_strlen(string);
    printf("%zu\n", len);
    int result = len == expected_len ? 1 : 0;
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strcmp_test(const char *string_1, const char *string_2, int expected_value) {
    printf("string_1 = '%s' string_2 = '%s'\n", string_1 ? string_1 : "NULL", string_2 ? string_2 : "NULL");
    int value = s21_strcmp(string_1, string_2);
    printf("%d\n", value);
    int result = (value == 0 && expected_value == 0) || (value < 0 && expected_value < 0) ||
                 (value > 0 && expected_value > 0);
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strcpy_test(const char *string, const char *expected_copy) {
    printf("%s\n", string ? string : "NULL");
    char target_string[1024];
    const char *copy = s21_strcpy(target_string, string);
    printf("%s\n", copy);
    int result = s21_strcmp(copy, expected_copy) == 0;
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strcat_test(const char *string_1, const char *string_2, const char *expected_string) {
    printf("string_1 = '%s' string_2 = '%s'\n", string_1 ? string_1 : "NULL", string_2 ? string_2 : "NULL");
    char target_string[1024];
    if (string_1) {
        s21_strcpy(target_string, string_1);
    }
    const char *string = s21_strcat(string_1 ? target_string : NULL, string_2);
    printf("%s\n", string);
    int result = s21_strcmp(string, expected_string) == 0;
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strchr_test(const char *string, char character, int expected_position) {
    printf("string = '%s' character = '%c'\n", string ? string : "NULL", character);
    const char *pointer = s21_strchr(string, character);
    printf("%s\n", pointer ? pointer : "NULL");
    int result = pointer == (expected_position < 0 ? NULL : string + expected_position);
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strstr_test(const char *string_1, const char *string_2, int expected_position) {
    printf("string_1 = '%s' string_2 = '%s'\n", string_1 ? string_1 : "NULL", string_2 ? string_2 : "NULL");
    const char *pointer = s21_strstr(string_1, string_2);
    printf("%s\n", pointer ? pointer : "NULL");
    int result = pointer == (expected_position < 0 ? NULL : string_1 + expected_position);
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

void s21_strtok_test(char *string_1, const char *string_2, const char *expected_word) {
    printf("string_1 = '%s' string_2 = '%s'\n", string_1 ? string_1 : "NULL", string_2 ? string_2 : "NULL");
    const char *word = s21_strtok(string_1, string_2);
    printf("%s\n", word ? word : "NULL");
    int result = s21_strcmp(word, expected_word) == 0;
    if (result) {
        printf("SUCCESS\n");
    } else {
        printf("FAIL\n");
    }
}

int main() {
#if QUEST >= 1
    printf("strlen_tests\n");
    s21_strlen_test(NULL, 0);
    s21_strlen_test("", 0);
    s21_strlen_test(" ", 1);
    s21_strlen_test("\n", 1);
    s21_strlen_test("\0", 0);
    s21_strlen_test("123", 3);
    s21_strlen_test("12 12 12 12 12 12", 17);
#endif
#if QUEST >= 2
    printf("strcmp_tests\n");
    s21_strcmp_test("asd", "qwe", -1);
    s21_strcmp_test("stringstring", "string", 1);
    s21_strcmp_test("a", "a", 0);
    s21_strcmp_test("", "", 0);
    s21_strcmp_test(NULL, "test", -1);
    s21_strcmp_test("", NULL, 1);
    s21_strcmp_test(NULL, NULL, 0);
#endif
#if QUEST >= 3
    printf("strcpy_tests\n");
    s21_strcpy_test("", "");
    s21_strcpy_test("asd", "asd");
    s21_strcpy_test("12 12 12 12 12 12", "12 12 12 12 12 12");
    s21_strcpy_test("string", "string");
    s21_strcpy_test(NULL, NULL);
#endif
#if QUEST >= 4
    printf("strcat_tests\n");
    s21_strcat_test("hello ", "world", "hello world");
    s21_strcat_test("asd", "", "asd");
    s21_strcat_test("", "test", "test");
    s21_strcat_test(NULL, "x", NULL);
    s21_strcat_test("x", NULL, NULL);
    s21_strcat_test(NULL, NULL, NULL);
#endif
#if QUEST >= 5
    printf("strchr_tests\n");
    s21_strchr_test("hello", 'l', 2);
    s21_strchr_test("string", 'z', -1);
    s21_strchr_test("", 'a', -1);
#endif
#if QUEST >= 6
    printf("strstr_tests\n");
    s21_strstr_test("hello", "ll", 2);
    s21_strstr_test("test", "test", 0);
    s21_strstr_test("abcabcd", "bcd", 4);
    s21_strstr_test("abcabc", "bcd", -1);
    s21_strstr_test("asdqwasdqw", "qw", 3);
    s21_strstr_test("", "string", -1);
    s21_strstr_test("string", "", 0);
    s21_strstr_test("", "", 0);
    s21_strstr_test("asd", NULL, -1);
    s21_strstr_test(NULL, "", -1);
    s21_strstr_test(NULL, NULL, -1);
#endif
#if QUEST >= 7
    printf("strtok_tests\n");
    s21_strtok_test(NULL, NULL, NULL);
    s21_strtok_test(NULL, " ", NULL);
    char strtok_test_1[] = "hello world";
    s21_strtok_test(strtok_test_1, " ", "hello");
    s21_strtok_test(NULL, " ", "world");
    s21_strtok_test(NULL, " ", NULL);
    char strtok_test_2[] = "  ( 1 \t\t + \n 2 \t )\n* -1\t ";
    s21_strtok_test(strtok_test_2, " \t\r\n", "(");
    s21_strtok_test(NULL, " \t\r\n", "1");
    s21_strtok_test(NULL, " \t\r\n", "+");
    s21_strtok_test(NULL, " \t\r\n", "2");
    s21_strtok_test(NULL, " \t\r\n", ")");
    s21_strtok_test(NULL, " \t\r\n", "*");
    s21_strtok_test(NULL, " \t\r\n", "-1");
    s21_strtok_test(NULL, " \t\r\n", NULL);
#endif
    return 0;
}