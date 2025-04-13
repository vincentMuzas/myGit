#pragma once

#define USAGE_MSG "Usage: %s <args>\n"

#define USAGE_PUSH_NAME "push"
#define USAGE_PUSH_DESC "Push changes to the remote repository.\n"
#define USAGE_PUSH_ARG 0

#define USAGE_PULL_NAME "pull"
#define USAGE_PULL_DESC "Pull changes from the remote repository.\n"
#define USAGE_PULL_ARG 0

#define USAGE_COMMIT_NAME "commit"
#define USAGE_COMMIT_DESC "Commit changes to the local repository.\n"
#define USAGE_COMMIT_ARG 0

#define USAGE_STATUS_NAME "status"
#define USAGE_STATUS_DESC "Show the status of the repository.\n"
#define USAGE_STATUS_ARG 0

#define USAGE_INIT_NAME "init"
#define USAGE_INIT_DESC "Initialize a new Git repository.\n"
#define USAGE_INIT_ARG 0

#define USAGE_CLONE_NAME "clone"
#define USAGE_CLONE_DESC "Clone a remote repository.\n"
#define USAGE_CLONE_ARG 1

#define USAGE_CHECKOUT_NAME "checkout"
#define USAGE_CHECKOUT_DESC "Switch branches or restore working tree files.\n"
#define USAGE_CHECKOUT_ARG 1

#define USAGE_ADD_NAME "add"
#define USAGE_ADD_DESC "Add file contents to the index.\n"
#define USAGE_ADD_ARG 2

#define USAGE_HELP_NAME "-h"
#define USAGE_HELP_DESC "Display this help message.\n"
#define USAGE_HELP_ARG 0

#define USAGE_ARGS_COUNT 9

typedef struct s_usage {
    char *name;
    char *desc;
    int need_arg;
    char *val;
} t_usage;

void print_usage(t_usage *usage);