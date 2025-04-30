#pragma once

#include <time.h>

typedef struct s_branches
{
    char branch_name[256];
    char origin[40];
} t_branches;

typedef struct s_commit
{
    char commit_message[256];
    char author[256];
    char committer[256];
    long nb_changes;
    char previous_hash[40];
    time_t commit_time;
} t_commit;

typedef struct s_commit_content
{
    char file_name[256];
    __int128_t file_size;
} t_commit_content;