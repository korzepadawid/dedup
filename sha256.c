#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <string.h>

#define BUFFER_SIZE 4096
#define SHA256_STRING_LENGTH (SHA256_DIGEST_LENGTH * 2 + 1)

void compute_sha256(const char *filename, char *digest)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    unsigned char buffer[BUFFER_SIZE];

    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("cant open file");
        return;
    }

    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0)
    {
        SHA256_Update(&sha256, buffer, bytesRead);
    }

    SHA256_Final(hash, &sha256);
    fclose(file);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        snprintf((char *)(digest + (i * 2)), 3, "%02x", hash[i]);
    }
    digest[SHA256_STRING_LENGTH - 1] = '\0';
}
