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
        color_red();
        fprintf(stderr, "Error: Could not open directory %s\n", path);
        color_reset();
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
        return FILE_NOT_FOUND;
    }
    long filesize;
    fseek(file, 0, SEEK_END);
    filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // TODO: Implement diff logic here
    t_blob last = get_latest_file_blob(latest_commit, path);
    if (last.blob == NULL)
    {
        fclose(file);
        return NEWFILE;
    }
    if (last.size != filesize)
    {
        free(last.blob);
        fclose(file);
        return MODIFIEDFILE;
    }
    // compare the file contents
    char *buffer = malloc(filesize);
    if (buffer == NULL)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        fclose(file);
        return ERROR;
    }
    if (fread(buffer, filesize, 1, file) != 1)
    {
        fprintf(stderr, "Error: Could not read file %s\n", path);
        free(buffer);
        free(last.blob);
        fclose(file);
        return ERROR;
    }
    if (memcmp(buffer, last.blob, filesize) != 0)
    {
        free(buffer);
        free(last.blob);
        fclose(file);
        return MODIFIEDFILE;
    }
    free(buffer);
    free(last.blob);

    fclose(file);
    return ERROR;
}

void print_diff_status(char *filepath, int status)
{
    switch (status)
    {
    case ERROR:
        color_red();
        printf("Error:\t%s unknown status\n", filepath);
        break;
    case FILE_NOT_FOUND:
        color_red();
        printf("File not found:\t%s\n", filepath);
        break;
    case NEWFILE:
        color_green();
        printf("New file:\t%s\n", filepath);
        break;
    case MODIFIEDFILE:
        color_yellow();
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