#pragma once
#include <stdio.h>

typedef struct {
  char owner[255];
  char repo[255];
  char rev[255];
  char sha256[255];
} Package;

int package_cmp(Package *old, Package *new);
void package_modify(Package *old, Package *new);
void package_update(Package *pkg, FILE *f);
void package_print(Package *pkg);
void package_dump(FILE *fp, Package *pkgs);
void package_load(FILE *fp, Package *pkg);
