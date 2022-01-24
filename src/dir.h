#pragma once
#include <sys/types.h>
#define MAX_LIST_SIZE 1024

typedef struct {
  size_t current;
  char strings[MAX_LIST_SIZE][255];
} List;

void list_print(List *list);

void walk_dir(const char *path, List *list);
