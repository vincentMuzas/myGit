#include "usage.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

t_usage *get_usage(int argc, char **argv) {
    static t_usage usage[USAGE_ARGS_COUNT + 1] = {
        {USAGE_PUSH_NAME, USAGE_PUSH_DESC, USAGE_ADD_ARG, NULL},
        {USAGE_PULL_NAME, USAGE_PULL_DESC, USAGE_PULL_ARG, NULL},
        {USAGE_COMMIT_NAME, USAGE_COMMIT_DESC, USAGE_COMMIT_ARG, NULL},
        {USAGE_STATUS_NAME, USAGE_STATUS_DESC, USAGE_STATUS_ARG, NULL},
        {USAGE_INIT_NAME, USAGE_INIT_DESC, USAGE_INIT_ARG, NULL},
        {USAGE_CLONE_NAME, USAGE_CLONE_DESC, USAGE_CLONE_ARG, NULL},
        {USAGE_CHECKOUT_NAME, USAGE_CHECKOUT_DESC, USAGE_CHECKOUT_ARG, NULL},
        {USAGE_ADD_NAME, USAGE_ADD_DESC, USAGE_ADD_ARG, NULL},
        {USAGE_HELP_NAME, USAGE_HELP_DESC, USAGE_HELP_ARG, NULL},
        {NULL, NULL, 0, NULL}  // Null-terminated array
    };
    for (int i = 0; i < USAGE_ARGS_COUNT; i++)
    {
        if (usage[i].name == NULL || usage[i].desc == NULL)
        {
            fprintf(stderr, "Error: Usage array is not properly initialized.\n");
            fprintf(stderr, "Array length: %i, Expected: %i\n", i, USAGE_ARGS_COUNT);
            exit(EXIT_FAILURE);
        }
    }
    for (size_t i = 0; i < USAGE_ARGS_COUNT; i++)
    {
        for (int j = 1; j < argc; j++)
        {
            if (strcmp(argv[j], usage[i].name) == 0)
            {
                if (usage[i].need_arg > 0 && j + 1 < argc)
                {
                    usage[i].val = argv[j + 1];
                    j++;
                }
                else if (usage[i].need_arg == 0)
                {
                    usage[i].val = usage[i].name;
                }
                else
                {
                    fprintf(stderr, "Error: %s requires an argument.\n", usage[i].name);
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    return usage;
}