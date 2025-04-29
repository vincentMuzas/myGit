#include "init.h"

int init(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);
    return init_repository();
}

int init_repository(void)
{
    t_branches *index = malloc(sizeof(t_branches));
    if (index == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    strcpy(index->branch_name, "master");
    index->origin[0] = '\0';

    DIR *dir = opendir("mydir");
    if (dir)
    {
        /* Directory exists. */
        closedir(dir);
    }
    else if (ENOENT == errno)
    {
        /* Directory does not exist. */
        mkdir(".mygit", 0755);
    }
    else
    {
        /* opendir() failed for some other reason. */
        fprintf(stderr, "Error: Could not open directory.\n");
        free(index);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(".mygit/index", "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not create index file.\n");
        free(index);
        return EXIT_FAILURE;
    }
    if (fwrite(index, sizeof(t_branches), 1, file) != 1)
    {
        fprintf(stderr, "Error: Could not write to index file.\n");
        fclose(file);
        free(index);
        return EXIT_FAILURE;
    }
    fclose(file);

    file = fopen(".mygit/HEAD", "wb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not create HEAD file.\n");
        free(index);
        return EXIT_FAILURE;
    }
    if (fprintf(file, "master\n") < 0)
    {
        fprintf(stderr, "Error: Could not write to HEAD file.\n");
        fclose(file);
        free(index);
        return EXIT_FAILURE;
    }
    fclose(file);

    free(index);
    printf("Initialized empty Git repository in .mygit/\n");

    return EXIT_SUCCESS;
}