#include "dir.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    printf("Usage: update ./path_to_start\n");
    return -1;
  }

  List list = {0};
  walk_dir(argv[1], &list);
  list_print(&list);

  return 0;
}
