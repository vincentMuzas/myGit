#pragma once

#define USAGE_MSG "Error\tthis function requires an argument\n"

#define USAGE_PUSH_NAME "push"
#define USAGE_PUSH_DESC "Push changes to the remote repository.\n"
#define USAGE_PUSH_ARG false

#define USAGE_PULL_NAME "pull"
#define USAGE_PULL_DESC "Pull changes from the remote repository.\n"
#define USAGE_PULL_ARG false

#define USAGE_COMMIT_NAME "commit"
#define USAGE_COMMIT_DESC "Commit changes to the local repository.\n"
#define USAGE_COMMIT_ARG false

#define USAGE_STATUS_NAME "status"
#define USAGE_STATUS_DESC "Show the status of the repository.\n"
#define USAGE_STATUS_ARG false

#define USAGE_INIT_NAME "init"
#define USAGE_INIT_DESC "Initialize a new Git repository.\n"
#define USAGE_INIT_ARG false

#define USAGE_CLONE_NAME "clone"
#define USAGE_CLONE_DESC "Clone a remote repository.\n"
#define USAGE_CLONE_ARG true

#define USAGE_CHECKOUT_NAME "checkout"
#define USAGE_CHECKOUT_DESC "Switch branches or restore working tree files.\n"
#define USAGE_CHECKOUT_ARG true

#define USAGE_ADD_NAME "add"
#define USAGE_ADD_DESC "Add file contents to the index.\n"
#define USAGE_ADD_ARG true

#define USAGE_HELP_NAME "-h"
#define USAGE_HELP_DESC "Display this help message.\n"
#define USAGE_HELP_ARG false

#define USAGE_ARGS_COUNT 9

#define NULL_USAGE {NULL, NULL, false, NULL}

// This macro is used to suppress unused variable warnings.
#define UNUSED(x) (void)(x)

typedef struct s_usage
{
    char *name;
    char *desc;
    char need_arg;
    int (*method)(int argc, char **argv);
} t_usage;

t_usage *get_usage();
t_usage parse_args(int argc, char **argv);
void print_usage();
void print_usage_line(t_usage usage);

int not_implemented(int argc, char **argv);