#include <stdio.h>
#include <stdlib.h>

#ifdef QUEST_1
#include "print_module.h"
#endif

#ifdef QUEST_2
#include "documentation_module.h"
#endif

int main() {
#ifdef QUEST_1
  print_log(print_char, Module_load_success_message);
#endif

#ifdef QUEST_2
  int *availability_mask = check_available_documentation_module(
      validate, Documents_count, Documents);

  // Output availability for each document....
  const char *document_names[Documents_count] = {Documents};
  for (int i = 0; i < Documents_count; ++i) {
    printf("%-15s: %s\n", document_names[i],
           availability_mask[i] ? "available" : "unavailable");
  }

  free(availability_mask);
#endif

  return 0;
}
