#include "diff.h"

int diff(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);
    return scandiffs(".");
}

int scandiffs(char *path)
{
    struct dirent *entry;
    DIR *dp = opendir(path);
    if (dp == NULL)
    {
        fprintf(stderr, "Error: Could not open directory %s\n", path);
        return EXIT_FAILURE;
    }
    while ((entry = readdir(dp)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            char file_path[512];
            snprintf(file_path, sizeof(file_path), "%s/%s", path, entry->d_name);
            check_diff(file_path);
        }
        else if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char new_path[512];
                snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
                scandiffs(new_path);
            }
        }
    }
    closedir(dp);
    return EXIT_SUCCESS;
}

int check_diff(char *path)
{
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", path);
        return EXIT_FAILURE;
    }
    // Implement diff logic here
    fclose(file);
    return EXIT_SUCCESS;
}