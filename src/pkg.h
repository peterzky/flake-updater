#pragma once
#include <stdio.h>

typedef struct {
  char owner[255];
  char repo[255];
  char rev[255];
  char sha256[255];
  char path[255];
} Package;

int package_cmp(Package *old, Package *new);
void package_modify(Package *old, Package *new);
void package_update(Package *pkg);
void package_print(Package *pkg);
void package_dump(Package *pkgs);
void package_load(const char *path, Package *pkg);
