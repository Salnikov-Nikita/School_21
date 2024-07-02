#include <stdio.h>
#include <time.h>

#include "print_module.h"

char print_char(char ch) { return putchar(ch); }

void print_log(char (*print)(char), char *message) {
  time_t now = time(NULL);
  char buf[16];
  strftime(buf, sizeof buf, "%H:%M:%S", localtime(&now));
  for (const char *s = Log_prefix; *s; s++) {
    print(*s);
  }
  print(' ');
  for (const char *s = buf; *s; s++) {
    print(*s);
  }
  print(' ');
  for (const char *s = message; *s; s++) {
    print(*s);
  }
}
