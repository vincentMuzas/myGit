#pragma once

#include "index.h"

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
// This macro is used to suppress unused variable warnings.
#define UNUSED(x) (void)(x)

int init_repository(void);