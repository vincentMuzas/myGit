#include "status.h"

int status(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);
    return status_func();
}

int status_func(void)
{
    t_index *index = malloc(sizeof(t_index));
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

    while (fread(index, sizeof(t_index), 1, file) == 1)
    {
        printf("=========================\n");
        printf("Branch: %s\n", index->branch_name);
        printf("Created on: %s", ctime(&index->created_on));
        printf("Origin: %s\n", index->origin);
    }

    fclose(file);
    free(index);
    return EXIT_SUCCESS;
}