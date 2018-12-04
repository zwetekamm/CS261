/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Zachary Wetekamm
 * Date: 11/26/18
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

int hashFunction1(const char* key)
{
    int r = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        r += key[i];
    }
    return r;
}


/**
 * Creates a new hash table link with a copy of the key string.
 * @param key Key string to copy in the link.
 * @param value Value to set in the link.
 * @param next Pointer to set as the link's next.
 * @return Hash table link allocated on the heap.
 */
HashLink* hashLinkNew(const char* key, int value, HashLink* next)
{
    HashLink* link = malloc(sizeof(HashLink));
    link->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(link->key, key);
    link->value = value;
    link->next = next;
    return link;
}

/**
 * Free the allocated memory for a hash table link created with hashLinkNew.
 * @param link
 */
static void hashLinkDelete(HashLink* link)
{
    free(link->key);
    free(link);
}

/**
 * Initializes a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param map
 * @param capacity The number of table buckets.
 */
void hashMapInit(HashMap* map, int capacity)
{
    map->capacity = capacity;
    map->size = 0;
    map->table = malloc(sizeof(HashLink*) * capacity);
    for (int i = 0; i < capacity; i++)
    {
        map->table[i] = NULL;
    }
}

/**
 * Removes all links in the map and frees all allocated memory. You can use
 * hashLinkDelete to free the links.
 * @param map
 */
void hashMapCleanUp(HashMap* map)
{
    assert(map != 0);

    for (int i = 0; i < map->capacity; i++) {
        HashLink *link = map->table[i];
        map->table[i] = NULL;

        while (link != NULL) {
            HashLink *temp = link;
            link = link->next;
            hashLinkDelete(temp);
        }
        free(map->table[i]);
    }
    free(map->table);
}

/**
 * Creates a hash table map, allocating memory for a link pointer table with
 * the given number of buckets.
 * @param capacity The number of buckets.
 * @return The allocated map.
 */
HashMap* hashMapNew(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    hashMapInit(map, capacity);
    return map;
}

/**
 * Removes all links in the map and frees all allocated memory, including the
 * map itself.
 * @param map
 */
void hashMapDelete(HashMap* map)
{
    hashMapCleanUp(map);
    free(map);
}

/**
 * Returns a pointer to the value of the link with the given key  and skip traversing as well. Returns NULL
 * if no link with that key is in the table.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return Link value or NULL if no matching link.
 */
int* hashMapGet(HashMap* map, const char* key)
{
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);
    HashLink *current = map->table[index];

    // Returns the pointer to the value of the key by comparing to passed argument key.
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return &(current->value);
        }
        current = current->next;
    }
    return NULL;
}

/**
 * Resizes the hash table to have a number of buckets equal to the given
 * capacity (double of the old capacity). After allocating the new table,
 * all of the links need to rehashed into it because the capacity has changed.
 *
 * Remember to free the old table and any old links if you use hashMapPut to
 * rehash them.
 *
 * @param map
 * @param capacity The new number of buckets.
 */
void resizeTable(HashMap* map, int capacity)
{
    int oldCap = hashMapCapacity(map);
    HashMap *temp = hashMapNew(capacity);

    for (int i = 0; i < oldCap; i++) {
        HashLink *current = map->table[i];

        while (current != NULL) {
            hashMapPut(temp, current->key, current->value);
            current = current->next;
        }
    }

    hashMapCleanUp(map);
    map->size = temp->size;
    map->table = temp->table;
    map->capacity = temp->capacity;

    temp->table = NULL;
    free(temp);
}

/**
 * Updates the given key-value pair in the hash table. If a link with the given
 * key already exists, this will just update the value and skip traversing. Otherwise, it will
 * create a new link with the given key and value and add it to the table
 * bucket's linked list. You can use hashLinkNew to create the link.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket.
 *
 * @param map
 * @param key
 * @param value
 */
void hashMapPut(HashMap* map, const char* key, int value)
{
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);

    if (hashMapTableLoad(map) >= MAX_TABLE_LOAD) {
        resizeTable(map, 2 * map->capacity);
    }

    if (index < 0) {
        index += map->capacity;
    }

    HashLink *link = map->table[index];
    HashLink *newLink = NULL;

    if (link == NULL) {
        newLink = hashLinkNew(key, value, NULL);
        map->table[index] = newLink;
        map->size++;
        return;
    } else {
        while (link != NULL) {
            if (strcmp(link->key, key) == 0) {
                link->value = value;
                return;
            }
            link = link->next;
        }

        newLink = hashLinkNew(key, value, map->table[index]);
        map->table[index] = newLink;
        map->size++;
        return;
    }

}

/**
 * Removes and frees the link with the given key from the table. If no such link
 * exists, this does nothing. Remember to search the entire linked list at the
 * bucket. You can use hashLinkDelete to free the link.
 * @param map
 * @param key
 */
void hashMapRemove(HashMap* map, const char* key)
{
    int index = HASH_FUNCTION(key) % hashMapCapacity(map);

    HashLink *current = map->table[index];
    HashLink *last = map->table[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (current == map->table[index]) {
                map->table[index] = current->next;
                hashLinkDelete(current);
            } else {
                last->next = current->next;
                hashLinkDelete(current);
            }
            map->size--;
            current = 0;
        } else {
            last = current;
            current = current->next;
        }
    }
}

/**
 * Returns 1 if a link with the given key is in the table and 0 otherwise.
 *
 * Use HASH_FUNCTION(key) and the map's capacity to find the index of the
 * correct linked list bucket. Also make sure to search the entire list.
 *
 * @param map
 * @param key
 * @return 1 if the key is found, 0 otherwise.
 */
int hashMapContainsKey(HashMap* map, const char* key)
{
    assert(map != NULL);
    assert(key != NULL);

    int mapCap = hashMapCapacity(map);
    int index = HASH_FUNCTION(key) % mapCap;

    if (index < 0) {
        index += mapCap;
    }

    HashLink *current = map->table[index];

    // Iterate current until key is found.
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}

/**
 * Returns the number of links in the table.
 * @param map
 * @return Number of links in the table.
 */
int hashMapSize(HashMap* map)
{
    assert(map != NULL);
    return map->size;
}

/**
 * Returns the number of buckets in the table.
 * @param map
 * @return Number of buckets in the table.
 */
int hashMapCapacity(HashMap* map)
{
    assert(map != NULL);
    return map->capacity;
}

/**
 * Returns the number of table buckets without any links.
 * @param map
 * @return Number of empty buckets.
 */
int hashMapEmptyBuckets(HashMap* map)
{
    int buckets = 0;
    int mapCap = hashMapCapacity(map);

    for (int i = 0; i < mapCap; i++) {
        if(map->table[i] == NULL) {
            buckets++;
        }
    }
    return buckets;
}

/**
 * Returns the ratio of (number of links) / (number of buckets) in the table.
 * Remember that the buckets are linked lists, so this ratio tells you nothing
 * about the number of empty buckets. Remember also that the load is a floating
 * point number, so don't do integer division.
 * @param map
 * @return Table load.
 */
float hashMapTableLoad(HashMap* map)
{
    float mapSize = (float) hashMapSize(map);
    float mapCap = (float) hashMapCapacity(map);

    return (mapSize / mapCap);
}

/**
 * Prints all the links in each of the buckets in the table.
 * @param map
 */
void hashMapPrint(HashMap* map)
{
    int mapCap = hashMapCapacity(map);

    for (int i = 0; i < mapCap; i++) {
        HashLink *link = map->table[i];

        if (link != NULL) {
            printf("\nBucket %i ->", i);
            while (link != NULL) {
                printf(" (%s, %d) ->", link->key, link->value);
                link = link->next;
            }
        }
    }
    printf("\n");
}
