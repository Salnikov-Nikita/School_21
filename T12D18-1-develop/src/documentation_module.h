#ifndef DOCUMENTATION_MODULE_H
#define DOCUMENTATION_MODULE_H

#include <stdio.h>
#include <string.h>

#define Documents "Linked lists", "Queues", "Maps", "Binary Trees"
#define Available_document "Binary Trees"
#define Documents_count 4

/*
    input: validation callback, documents count, args with documents names (max
   16) output: binary mask of documents availability
*/
int *check_available_documentation_module(int (*validate)(char *),
                                          int document_count, ...);

int validate(char *data);

#endif // DOCUMENTATION_MODULE_H
