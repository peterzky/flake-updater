#include "dir.h"
#include "pkg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    printf("Usage: update ./path_to_start\n");
    return -1;
  }

  List list = {0};
  walk_dir(argv[1], &list);

  Package pkgs[list.current];

  for (size_t i = 0; i < list.current; ++i) {
    FILE *f = fopen(list.strings[i], "r");
    package_load(f, &pkgs[i]);
    fclose(f);
  }

  for (size_t i = 0; i < list.current; ++i) {
    FILE *f = fopen(list.strings[i], "w");
    package_update(&pkgs[i], f);
    fclose(f);
  }

  return 0;
}
