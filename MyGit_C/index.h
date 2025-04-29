#pragma once

#include <time.h>

typedef struct s_index
{
    char branch_name[256];
    char origin[256];
    time_t created_on;
} t_index;