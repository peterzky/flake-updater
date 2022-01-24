#include "dir.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    printf("Usage: update ./path_to_start\n");
    return -1;
  }

  /* printf("%s", argv[1]); */
  walk_dir(argv[1]);

  return 0;
}
