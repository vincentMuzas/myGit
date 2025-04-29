#include "branch.h"

int branch(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);
    return branch_func();
}

int branch_func(void)
{
    t_branches *index = malloc(sizeof(t_branches));
    if (index == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    FILE *file = fopen(".mygit/index", "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open index file.\n");
        free(index);
        return EXIT_FAILURE;
    }

    while (fread(index, sizeof(t_branches), 1, file) == 1)
    {
        printf("=========================\n");
        printf("Branch: %s\n", index->branch_name);
        printf("Origin: %s\n", index->origin);
    }

    fclose(file);
    free(index);
    return EXIT_SUCCESS;
}