#include "pkg.h"
#include <json-c/json.h>
#include <stdio.h>
#include <string.h>

int package_cmp(Package *old, Package *new) {
  if (strcmp(new->rev, old->rev) == 0) {
    printf("Package: %s/%s is latest\n", old->owner, old->repo);
    return 1;
  }
  return 0;
}

void package_modify(Package *old, Package *new) {
  printf("Package: %s/%s, updated rev: %s -> %s\n", old->owner, old->repo,
         old->rev, new->rev);
  strcpy(old->rev, new->rev);
  strcpy(old->sha256, new->sha256);
}

void package_print(Package *pkg) {
  printf("owner: %s\nrepo: %s\nrev: %s\nsha256: %s\n", pkg->owner, pkg->repo,
         pkg->rev, pkg->sha256);
}

void package_dump(Package *pkg) {
  FILE *fp;
  fp = fopen(pkg->path, "w");
  fprintf(fp,
          "{\n  'owner':'%s',\n  'repo':'%s',\n  'rev': '%s',\n  "
          "'sha256':'%s'\n}\n",
          pkg->owner, pkg->repo, pkg->rev, pkg->sha256);
  fclose(fp);
}

void package_load(const char *path, Package *pkg) {
  FILE *f;
  f = fopen(path, "r");
  char buffer[1024];
  fread(buffer, 1024, 1, f);
  fclose(f);

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

  strcpy(pkg->path, path);
  strcpy(pkg->owner, json_object_get_string(owner));
  strcpy(pkg->repo, json_object_get_string(repo));
  strcpy(pkg->rev, json_object_get_string(rev));
  strcpy(pkg->sha256, json_object_get_string(sha256));

}

void package_load_prefetch(FILE *fp, Package *pkg) {
  char buffer[1024];
  fread(buffer, 1024, 1, fp);
  struct json_object *parsed_json;
  struct json_object *rev;
  struct json_object *sha256;
  parsed_json = json_tokener_parse(buffer);
  json_object_object_get_ex(parsed_json, "rev", &rev);
  json_object_object_get_ex(parsed_json, "sha256", &sha256);
  strcpy(pkg->rev, json_object_get_string(rev));
  strcpy(pkg->sha256, json_object_get_string(sha256));
}

void package_update(Package *pkg) {
  char command[255] = {0};
  Package updated_pkg = {0};
  sprintf(command, "nix-prefetch-git --quiet https://github.com/%s/%s.git",
          pkg->owner, pkg->repo);
  printf("%s\n", command);
  FILE *fp = popen(command, "r");
  package_load_prefetch(fp, &updated_pkg);
  fclose(fp);
  if (package_cmp(pkg, &updated_pkg) == 0) {
    package_modify(pkg, &updated_pkg);
    package_dump(pkg);
  }
}
