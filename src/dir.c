#define _DEFAULT_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

void walk_dir(const char *path) {
  DIR *dir;

  struct dirent *ent;

  dir = opendir(path);

  while ((ent = readdir(dir)) != NULL) {

    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
      continue;
    }
    char next_path[255];
    if (ent->d_type == DT_DIR) {
      sprintf(next_path, "%s/%s", path, ent->d_name);
      walk_dir(next_path);
    }

    if (ent->d_type == DT_REG)
      sprintf(next_path, "%s/%s", path, ent->d_name);
    printf("%s\n", next_path);
  }

  (void)closedir(dir);
}
