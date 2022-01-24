#define _DEFAULT_SOURCE
#include "dir.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void list_print(List *list) {
  for (size_t i = 0; i < list->current; ++i)
    printf("%s\n", list->strings[i]);
}

void list_push(List *list, const char *path) {
  strcpy(list->strings[list->current], path);
  list->current++;
}

void walk_dir(const char *path, List *list) {
  DIR *dir;
  char next_path[255];
  char suffix[5];
  struct dirent *ent;

  dir = opendir(path);

  while ((ent = readdir(dir)) != NULL) {
    // ignore dot directories
    if (ent->d_name[0] == '.' || ent->d_name[1] == '.')
      continue;

    if (ent->d_type == DT_DIR) {
      sprintf(next_path, "%s/%s", path, ent->d_name);
      walk_dir(next_path, list);
    }

    if (ent->d_type == DT_REG) {

      strcpy(suffix, &ent->d_name[strlen(ent->d_name) - 4]);
      if (strcmp(suffix, "json") == 0) {
        sprintf(next_path, "%s/%s", path, ent->d_name);
        list_push(list, next_path);
      }
    }
  }

  (void)closedir(dir);
}
