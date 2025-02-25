#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <openssl/sha.h>

#include "map.h"
#include "sha256.h"

#define SHA256_STRING_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

void find_dup(const char *path);

bool is_dir(const char *path);

void walk_dir(const char *path);

void handle_file(const char *filepath, const char *filename, struct map *map);

int main(const int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("Unexpected number of arguments");
        exit(EXIT_FAILURE);
    }

    const char *path = argv[1];
    find_dup(path);

    return 0;
}

void find_dup(const char *path)
{
    printf("looking for duplicates in %s\n", path);

    if (!is_dir(path))
    {
        perror("Not a directory");
        exit(EXIT_FAILURE);
    }

    walk_dir(path);
}

bool is_dir(const char *path)
{
    DIR *dir;
    if ((dir = opendir(path)) != NULL)
    {
        struct dirent *entry;
        if ((entry = readdir(dir)) != NULL)
        {
            closedir(dir);
            return entry->d_type == DT_DIR;
        }
        closedir(dir);
    }
    return false;
}

void walk_dir(const char *path)
{
    DIR *dir;
    struct map m;
    map_init(&m);

    if ((dir = opendir(path)) != NULL)
    {
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG)
            {
                handle_file(path, entry->d_name, &m);
            }
        }
        closedir(dir);
    }
}

void handle_file(const char *filepath, const char *filename, struct map *map)
{
    char *full_path = (char *)calloc(strlen(filepath) + strlen(filename) + 2, sizeof(char));
    snprintf(full_path, strlen(filepath) + strlen(filename) + 1, "%s%s", filepath, filename);

    char digest[SHA256_STRING_LENGTH];
    compute_sha256(full_path, digest);

    if (map_get(map, digest, SHA256_STRING_LENGTH) != NULL)
    {
        printf("Found a duplicate: %s\n", full_path);
    }
    else
    {
        map_put(map, digest, SHA256_STRING_LENGTH, full_path);
    }

    free(full_path);
}
