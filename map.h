#ifndef MAP_H
#define MAP_H

#include <stddef.h>

#define MAP_SIZE 1024

/**
 * Hash map structure definition.
 */
struct map {
    char *items[MAP_SIZE];
};

/**
 * Computes the hash value of a given key using the djb2 hash function.
 *
 * @param key The input key to be hashed.
 * @param length The length of the key.
 * @return The computed hash value.
 */
unsigned long hash(const char *key, size_t length);

/**
 * Initializes the hash map by setting all entries to NULL.
 *
 * @param map Pointer to the map structure to be initialized.
 */
void map_init(struct map *map);

/**
 * Retrieves a value from the map based on a given key.
 *
 * @param map Pointer to the map structure.
 * @param key The key to look up.
 * @param key_length The length of the key.
 * @return The value associated with the key, or NULL if not found.
 */
char *map_get(const struct map *map, const char *key, size_t key_length);

/**
 * Inserts a key-value pair into the hash map.
 *
 * @param map Pointer to the map structure.
 * @param key The key to be inserted.
 * @param key_length The length of the key.
 * @param value The value associated with the key.
 */
void map_put(struct map *map, const char *key, size_t key_length, const char *value);

/**
 * Deletes a key from the hash map.
 *
 * @param map Pointer to the map structure.
 * @param key The key to be deleted.
 * @param key_length The length of the key.
 */
void map_delete(struct map *map, const char *key, size_t key_length);

#endif
