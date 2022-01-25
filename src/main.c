#include "dir.h"
#include "pkg.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *thread_runner(void *arg) {
  Package *pkg = arg;
  package_update(pkg);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    printf("Usage: update ./path_to_start\n");
    return -1;
  }

  List list = {0};
  walk_dir(argv[1], &list);

  const size_t count = list.current;

  Package pkgs[count];

  for (size_t i = 0; i < count; ++i) {
    package_load(list.strings[i], &pkgs[i]);
  }

  // update in parallel
  pthread_t threads[count];

  for (size_t i = 0; i < count; ++i) {
    pthread_create(&threads[i], NULL, thread_runner, (void *)&pkgs[i]);
  }

  for (size_t i = 0; i < count; ++i) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
