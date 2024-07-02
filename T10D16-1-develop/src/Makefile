CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
LDFLAGS=

all: strlen_tests strcmp_tests strcpy_tests strcat_tests strchr_tests strstr_tests strtok_tests text_processor

strlen_tests: ../build/Quest_1
strcmp_tests: ../build/Quest_2
strcpy_tests: ../build/Quest_3
strcat_tests: ../build/Quest_4
strchr_tests: ../build/Quest_5
strstr_tests: ../build/Quest_6
strtok_tests: ../build/Quest_7
text_processor: ../build/Quest_8
	
../build/Quest_%: s21_string.o s21_string_test_%.o
	$(CC) $(LDLAGS) $^ -o $@

../build/Quest_8: s21_string.o text_processor.o 
	$(CC) $(LDLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

s21_string_test_%.o: s21_string_test.c
	$(CC) $(CFLAGS) -DQUEST=$* $< -o $@

clean:
	rm -f *.o ../build/Quest_*

rebuild:
	$(MAKE) clean
	$(MAKE) all