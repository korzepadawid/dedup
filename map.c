#include "map.h"
#include <stdlib.h>
#include <string.h>

#define DJB2_INIT 5381

/**
 * Computes the hash value of a given key using the djb2 hash function.
 * Reference: http://www.cse.yorku.ca/~oz/hash.html
 *
 * @param key The input key to be hashed.
 * @param length The length of the key.
 * @return The computed hash value.
 */
unsigned long hash(const char *key, const size_t length)
{
    unsigned long hash = DJB2_INIT;
    for (size_t i = 0; i < length; i++)
    {
        hash = (hash << 5) + hash + (unsigned char)key[i];
    }
    return hash;
}

/**
 * Initializes the hash map by setting all entries to NULL.
 *
 * @param map Pointer to the map structure to be initialized.
 */
void map_init(struct map *map)
{
    if (map == NULL)
    {
        return;
    }
    memset(map, 0, sizeof(*map));
}

/**
 * Retrieves a value from the map based on a given key.
 *
 * @param map Pointer to the map structure.
 * @param key The key to look up.
 * @param key_length The length of the key.
 * @return The value associated with the key, or NULL if not found.
 */
char *map_get(const struct map *map, const char *key, const size_t key_length)
{
    if (!map || !key)
    {
        return NULL;
    }

    const unsigned long index = hash(key, key_length) % MAP_SIZE;
    return map->items[index];
}

/**
 * Inserts a key-value pair into the hash map.
 *
 * @param map Pointer to the map structure.
 * @param key The key to be inserted.
 * @param key_length The length of the key.
 * @param value The value associated with the key.
 */
void map_put(struct map *map, const char *key, const size_t key_length, const char *value)
{
    if (!map || !key || !value)
    {
        return;
    }
    const unsigned long index = hash(key, key_length) % MAP_SIZE;
    if (map->items[index] != NULL)
    {
        free(map->items[index]);
    }
    map->items[index] = strdup(value);
}

/**
 * Deletes a key from the hash map by freeing its value and setting it to NULL.
 *
 * @param map Pointer to the map structure.
 * @param key The key to be deleted.
 * @param key_length The length of the key.
 */
void map_delete(struct map *map, const char *key, const size_t key_length)
{
    if (!map || !key)
    {
        return;
    }
    const unsigned long index = hash(key, key_length) % MAP_SIZE;
    free(map->items[index]);
    map->items[index] = NULL;
}
