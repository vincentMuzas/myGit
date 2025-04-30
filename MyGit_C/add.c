#include "add.h"

int add(int argc, char **argv)
{
    char *path = NULL;
    if (argc == 0)
    {
        fprintf(stderr, "Error: No files specified to add.\n");
        return EXIT_FAILURE;
    }

    char *head_name = get_head_name();
    char *latest_commit = get_latest_commit(head_name);

    FILE *file = NULL;
    FILE *staging = NULL;

    staging = fopen(".mygit/STAGING", "a+b");
    if (staging == NULL)
    {
        fprintf(stderr, "Error: Could not open staging file.\n");
        free(head_name);
        if (latest_commit != NULL)
            free(latest_commit);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < argc; i++)
    {
        if (argv[i][0] == '.' && argv[i][1] == '/')
        {
            path = malloc(strlen(argv[i]) + 1);
            if (path == NULL)
            {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                return EXIT_FAILURE;
            }
            strncpy(path, argv[i], strlen(argv[i]) + 1);
        }
        else
        {
            path = malloc(strlen(argv[i]) + 3);
            if (path == NULL)
            {
                fprintf(stderr, "Error: Memory allocation failed.\n");
                return EXIT_FAILURE;
            }
            snprintf(path, strlen(argv[i]) + 3, "./%s", argv[i]);
        }

        // check if the file is already in the staging area
        FILE *staging_check = fopen(".mygit/STAGING", "r");
        if (staging_check == NULL)
        {
            fprintf(stderr, "Error: Could not open staging file.\n");
            free(path);
            free(head_name);
            if (latest_commit != NULL)
                free(latest_commit);
            return EXIT_FAILURE;
        }
        char line[256];
        int found = 0;
        while (fgets(line, sizeof(line), staging_check) != NULL)
        {
            // remove the newline character
            line[strcspn(line, "\n")] = 0;
            if (strcmp(line, path) == 0)
            {
                found = 1;
                color_red();
                printf("File %s is already in the staging area.\n", path);
                color_reset();
                break;
            }
        }
        fclose(staging_check);
        if (found)
        {
            free(path);
            path = NULL;
            continue;
        }

        file = fopen(path, "rb");
        if (file == NULL)
        {
            fprintf(stderr, "Error: Could not open file %s\n", path);
            continue;
        }
        fclose(file);
        // check if the file is modified
        int status = check_diff(path, latest_commit);
        switch (status)
        {
        case NEWFILE:
            color_green();
            printf("New file: %s\n", path);
            break;

        case MODIFIEDFILE:
            color_yellow();
            printf("Modified file: %s\n", path);
            break;
        case DELETEDFILE:
            color_purple();
            printf("Deleted file: %s\n", path);
            break;
        case UNCHANGEDFILE:
            color_red();
            printf("Unchanged file: %s\n", path);
            break;
        case FILE_NOT_FOUND:
            color_red();
            printf("File not found: %s\n", path);
            break;
        default:
            fprintf(stderr, "Error: Unknown status for file %s\n", path);
            break;
        }
        color_reset();
        // Add the file to the Staging area
        if (status == NEWFILE || status == MODIFIEDFILE || status == DELETEDFILE)
        {
            fprintf(staging, "%s\n", path);
        }
    }
    fclose(staging);
    free(head_name);
    if (path != NULL)
        free(path);
    if (latest_commit != NULL)
        free(latest_commit);
    return EXIT_SUCCESS;
}