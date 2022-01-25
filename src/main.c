#include "dir.h"
#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char owner[255];
  char repo[255];
  char rev[255];
  char sha256[255];
} Package;

void package_print(Package *pkg) {
  printf("owner: %s\nrepo: %s\nrev: %s\nsha256: %s\n", pkg->owner, pkg->repo,
         pkg->rev, pkg->sha256);
}

void package_load(const char *path, Package *pkg) {
  FILE *fp;
  char buffer[1024];
  fp = fopen(path, "rb");
  fread(buffer, 1024, 1, fp);
  fclose(fp);

  struct json_object *parsed_json;
  struct json_object *owner;
  struct json_object *repo;
  struct json_object *rev;
  struct json_object *sha256;

  parsed_json = json_tokener_parse(buffer);
  json_object_object_get_ex(parsed_json, "owner", &owner);
  json_object_object_get_ex(parsed_json, "repo", &repo);
  json_object_object_get_ex(parsed_json, "rev", &rev);
  json_object_object_get_ex(parsed_json, "sha256", &sha256);

  strcpy(pkg->owner, json_object_get_string(owner));
  strcpy(pkg->repo, json_object_get_string(repo));
  strcpy(pkg->rev, json_object_get_string(rev));
  strcpy(pkg->sha256, json_object_get_string(sha256));
}

int main(int argc, char *argv[]) {
  if (argc < 2 || argc > 3) {
    printf("Usage: update ./path_to_start\n");
    return -1;
  }

  List list = {0};
  walk_dir(argv[1], &list);
  /* list_print(&list); */

  Package pkgs[list.current];

  for (size_t i = 0; i < list.current; ++i) {
    package_load(list.strings[i], &pkgs[i]);
    package_print(&pkgs[i]);
    printf("\n");
  }

  return 0;
}
