#pragma once

#include "status.h"

t_blob get_latest_file_blob(char *commit_hash, char *file_name);
char *get_head_name(void);
char *get_latest_commit(char *head_name);