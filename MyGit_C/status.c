#include "status.h"

int status(int argc, char **argv)
{
    UNUSED(argc);
    UNUSED(argv);
    char *head_name = get_head_name();
    char *latest_commit = get_latest_commit(head_name);
    int return_value = 0;

    printf("Current branch: %s\n", head_name);
    printf("Latest commit: %s\n", latest_commit);
    if (latest_commit == NULL)
    {
        fprintf(stderr, "Error: Could not get latest commit or no commit history.\n");
    }
    return_value = scandiffs(".", latest_commit);
    if (head_name != NULL)
        free(head_name);
    if (latest_commit != NULL)
        free(latest_commit);
    return return_value;
}

int scandiffs(char *path, char *latest_commit)
{
    struct dirent *entry;
    int diff_status;
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
            diff_status = check_diff(file_path, latest_commit);
            print_diff_status(file_path, diff_status);
        }
        else if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char new_path[512];
                snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
                scandiffs(new_path, latest_commit);
            }
        }
    }
    closedir(dp);
    return EXIT_SUCCESS;
}

int check_diff(char *path, char *latest_commit)
{
    if (latest_commit == NULL)
    {
        return NEWFILE;
    }
    FILE *file = fopen(path, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", path);
        return FILE_NOT_FOUND;
    }
    // TODO: Implement diff logic here
    fclose(file);
    return EXIT_SUCCESS;
}

char *get_latest_commit(char *head_name)
{
    FILE *index = fopen(".mygit/index", "rb");
    if (index == NULL)
    {
        fprintf(stderr, "Error: Could not open index file.\n");
        return NULL;
    }
    t_branches branch;
    while (fread(&branch, sizeof(t_branches), 1, index) == 1)
    {
        if (strcmp(branch.branch_name, head_name) == 0)
        {
            fclose(index);
            char *commit_hash = malloc(41);
            snprintf(commit_hash, 40, "%s", branch.origin);
            return commit_hash;
        }
    }
    char *diff_path = malloc(256);
    snprintf(diff_path, 256, ".mygit/commits/%s", head_name);
    // check if the file exists
    FILE *file = fopen(diff_path, "rb");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open file %s\n", diff_path);
        free(diff_path);
        fclose(index);
        return NULL;
    }
    fclose(file);
    free(diff_path);
    char *commit_hash = malloc(41);
    snprintf(commit_hash, 40, "%s", head_name);
    fclose(index);
    return commit_hash;
}

char *get_head_name(void)
{
    FILE *file = fopen(".mygit/HEAD", "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open HEAD file.\n");
        return NULL;
    }
    char *head_name = malloc(256);
    if (head_name == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }
    if (fgets(head_name, 256, file) == NULL)
    {
        fprintf(stderr, "Error: Could not read HEAD file.\n");
        free(head_name);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return head_name;
}

void print_diff_status(char *filepath, int status)
{
    switch (status)
    {
    case FILE_NOT_FOUND:
        color_red();
        printf("File not found:\t%s\n", filepath);
        break;
    case NEWFILE:
        color_green();
        printf("New file:\t%s\n", filepath);
        break;
    case MODIFIEDFILE:
        yellow();
        printf("Modified file:\t%s\n", filepath);
        break;
    case DELETEDFILE:
        color_red();
        printf("Deleted file.\t%s\n", filepath);
        break;
    default:
        color_magenta();
        printf("Unknown status:\t%s\n", filepath);
        break;
    }
    color_reset();
}