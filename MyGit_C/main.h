#pragma once

#include "usage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

t_usage *get_usage(int argc, char **argv);
int parse_args(int argc, char *argv[]);