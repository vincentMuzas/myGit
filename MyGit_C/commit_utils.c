#include "commit_utils.h"

t_blob get_latest_file_blob(char *commit_hash, char *file_name)
{
    FILE *file;
    t_commit commit;
    t_commit_content commit_content;
    t_blob blob;
    blob.size = -1;
    blob.blob = NULL;

    while (commit_hash != NULL && strcmp(commit_hash, "") != 0)
    {
        // get the commit file path
        char commit_path[256];
        snprintf(commit_path, sizeof(commit_path), ".mygit/commits/%s", commit_hash);
        file = fopen(commit_path, "rb");
        if (file == NULL)
        {
            fprintf(stderr, "Error: Could not open commits file.\n");
            return blob;
        }
        if (fread(&commit, sizeof(t_commit), 1, file) != 1)
        {
            fprintf(stderr, "Error: Could not read commit file.\n");
            fclose(file);
            return blob;
        }

        while (fread(&commit_content, sizeof(t_commit_content), 1, file) == 1)
        {
            if (strcmp(commit_content.file_name, file_name) == 0)
            {
                blob.blob = malloc(commit_content.file_size);
                if (blob.blob == NULL)
                {
                    fprintf(stderr, "Error: Memory allocation failed.\n");
                    fclose(file);
                    return blob;
                }
                if (fread(blob.blob, commit_content.file_size, 1, file) != 1)
                {
                    fprintf(stderr, "Error: Could not read the blob %s\n", commit_content.file_name);
                    free(blob.blob);
                    blob.blob = NULL;
                    blob.size = -1;
                    fclose(file);
                    return blob;
                }
                blob.size = commit_content.file_size;
                fclose(file);
                return blob;
            }
            fseek(file, commit_content.file_size, SEEK_CUR);
        }
        fclose(file);
        commit_hash = commit.previous_hash;
    }
    return blob;
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
            snprintf(commit_hash, 20, "%s", branch.origin);
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
    snprintf(commit_hash, 20, "%s", head_name);
    fclose(index);
    return commit_hash;
}
