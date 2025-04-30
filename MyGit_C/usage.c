#include "usage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

t_usage parse_args(int argc, char **argv)
{
    t_usage *usage = get_usage();
    t_usage selected_usage = NULL_USAGE;
    for (int i = 0; i < USAGE_ARGS_COUNT; i++)
    {
        if (usage[i].name == NULL || usage[i].desc == NULL)
        {
            fprintf(stderr, "Error: Usage array is not properly initialized.\n");
            fprintf(stderr, "Array length: %i, Expected: %i\n", i, USAGE_ARGS_COUNT);
            exit(EXIT_FAILURE);
        }
    }
    if (argc < 2)
    {
        print_usage();
        return selected_usage;
    }
    char found = false;
    for (size_t i = 0; i < USAGE_ARGS_COUNT; i++)
    {
        if (strcmp(argv[1], usage[i].name) == 0)
        {
            if (usage[i].need_arg == 1 && argc <= 2)
            {
                fprintf(stderr, USAGE_MSG);
                print_usage_line(usage[i]);
                found = true;
                break;
            }
            else
            {
                found = true;
                selected_usage = usage[i];
                break;
            }
        }
    }
    if (!found)
    {
        fprintf(stderr, "Error: Unknown command '%s'.\n\n", argv[1]);
        print_usage();
    }
    return selected_usage;
}

t_usage *get_usage()
{
    static t_usage usage[USAGE_ARGS_COUNT + 1] = {
        {USAGE_INIT_NAME, USAGE_INIT_DESC, USAGE_INIT_ARG, &init},
        {USAGE_BRANCH_NAME, USAGE_BRANCH_DESC, USAGE_BRANCH_ARG, &branch},
        {USAGE_STATUS_NAME, USAGE_STATUS_DESC, USAGE_STATUS_ARG, &status},
        {USAGE_DIFF_NAME, USAGE_DIFF_DESC, USAGE_DIFF_ARG, &not_implemented},
        {USAGE_PUSH_NAME, USAGE_PUSH_DESC, USAGE_ADD_ARG, &not_implemented},
        {USAGE_PULL_NAME, USAGE_PULL_DESC, USAGE_PULL_ARG, &not_implemented},
        {USAGE_COMMIT_NAME, USAGE_COMMIT_DESC, USAGE_COMMIT_ARG, &not_implemented},
        {USAGE_CLONE_NAME, USAGE_CLONE_DESC, USAGE_CLONE_ARG, &not_implemented},
        {USAGE_CHECKOUT_NAME, USAGE_CHECKOUT_DESC, USAGE_CHECKOUT_ARG, &not_implemented},
        {USAGE_ADD_NAME, USAGE_ADD_DESC, USAGE_ADD_ARG, &not_implemented},
        {USAGE_HELP_NAME, USAGE_HELP_DESC, USAGE_HELP_ARG, &not_implemented},
        NULL_USAGE // Null-terminated array
    };
    return usage;
}

int not_implemented(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);
    // This function is a placeholder for features not yet implemented.
    fprintf(stderr, "Error: this feature is not implemented yet.\n");
    return 1;
}

void print_usage()
{
    t_usage *usage = get_usage();
    fprintf(stderr, USAGE_MSG);
    for (int i = 0; usage[i].name != NULL; i++)
    {
        print_usage_line(usage[i]);
    }
}

void print_usage_line(t_usage usage)
{
    fprintf(stderr, "%s:\t%s %s",
            usage.name,
            usage.need_arg ? "<arg>" : "",
            usage.desc);
}