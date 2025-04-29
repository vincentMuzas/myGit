#pragma once

#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// This macro is used to suppress unused variable warnings.
#define UNUSED(x) (void)(x)

void scandiffs(char *path);

int check_diff(char *path);