#pragma once

#include "index.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// This macro is used to suppress unused variable warnings.
#define UNUSED(x) (void)(x)

#define ERROR -1
#define FILE_NOT_FOUND 0
#define NEWFILE 1
#define MODIFIEDFILE 2
#define DELETEDFILE 3
#define UNCHANGEDFILE 4

typedef struct s_blob
{
    long size;
    char *blob;
} t_blob;

int scandiffs(char *path, char *latest_commit);

int check_diff(char *path, char *latest_commit);

char *get_current_branch();

char *get_latest_commit(char *head_name);

char *get_head_name(void);

void print_latest_commit(char *commit_hash);

int get_commit_hash(char *commit_hash, char *file_name);

void print_diff_status(char *filepath, int status);

t_blob get_latest_file_blob(char *commit_hash, char *file_name);