#include "documentation_module.h"

#include <stdarg.h>
#include <stdlib.h>

int validate(char *data) {
  int validation_result = !strcmp(data, Available_document);
  return validation_result;
}

int *check_available_documentation_module(int (*validate)(char *),
                                          int document_count, ...) {
  int *result = calloc(document_count, sizeof(int));
  va_list va;
  va_start(va, document_count);
  for (int i = 0; i < document_count; ++i) {
    char *data = va_arg(va, char *);
    result[i] = validate(data);
  }
  va_end(va);
  return result;
}
