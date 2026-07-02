/**
 * @file store.c
 *
 * @brief simple store using a B-tree implementation
 *
 ***************************************************************************************************
 *
 ***************************************************************************************************
 */
#include <stdint.h> /* uint8_t */
#include <stddef.h> /* NULL, size_t */
#include <stdlib.h> /* malloc, free, EXIT_SUCCESS and EXIT_FAILURE */
#include <string.h> /* strncmp */
#include <assert.h> /* assert */

#include "store.h"
#include "btree.h"

#define STORE_BTREE_MIN_DEGREE (25) /* Minimum degree for the B-tree */
#define STORE_PAGE_SIZE (16384)     /* Size of each page in the store */

#define STORE_ERR_OK (0)     /* Return value for successful operations */
#define STORE_ERR_ALLOC (-1) /* Return value for memory allocation failures */
#define STORE_ERR_FULL (-2)  /* Return value for full store  */

// /**
//  *  @brief buffer with length
//  */
// typedef struct _buf
// {
//     uint8_t *prt; /* Pointer to the data buffer */
//     size_t len;   /* Size of the data buffer */
// } buf_t;

// /**
//  *  @brief Buffer with length and a capacity
//  */
// typedef struct _vec
// {
//     uint8_t *prt;    /* Pointer to the data buffer */
//     size_t len;      /* Size of the data buffer */
//     size_t capacity; /* Capacity of the data buffer */
// } vec_t;

/**
 * @brief The Key value
 */
typedef struct _key_value
{
    const uint8_t *key;
    size_t key_len;
    size_t val_len;
} key_value_t;

/**
 * @brief The store
 */
typedef struct _store
{
    uint8_t *store;   /* The store for the key values */
    size_t capacity;  /* Capacity of the data buffer */
    uint8_t *free;    /* Pointer to the free space in the store */
    size_t remaining; /* Remaining space in the store */
    btree_t *index;   /* The index as a B-tree */
} store_t;

/**
 * @brief Comparison function for the key_value_t
 *
 * @param lh Left-hand side item
 * @param rh Right-hand side item
 *
 * @return Negative value if lh < rh, zero if lh == rh, positive value if lh > rh
 */
int key_value_compare(const void *lh, const void *rh)
{
    const key_value_t *left = (const key_value_t *)lh;
    const key_value_t *right = (const key_value_t *)rh;

    size_t min_len = left->key_len < right->key_len ? left->key_len : right->key_len;
    int comp = strncmp((char *)left->key, (char *)right->key, min_len);
    if (comp == 0)
    {
        if (left->key_len < right->key_len)
        {
            return -1;
        }
        else if (left->key_len > right->key_len)
        {
            return 1;
        }
    }
    return comp;
}

/**************************************************************************************************
 * The API
 *************************************************************************************************/

store_t *store_init(size_t pages)
{

    store_t *store = malloc(sizeof(store_t));
    if (store == NULL)
    {
        return NULL;
    }
    store->store = malloc(pages * STORE_PAGE_SIZE);
    if (store->store == NULL)
    {
        free(store);
        return NULL;
    }
    store->remaining = pages * STORE_PAGE_SIZE;

    store->index = btree_init(STORE_BTREE_MIN_DEGREE, sizeof(key_value_t), &key_value_compare);
    if (store->index == NULL)
    {
        free(store);
        return NULL;
    }
    return store;
}

void store_deinit(store_t **store)
{
    if (store == NULL || *store == NULL)
    {
        return;
    }

    btree_deinit(&(*store)->index);
    free(*store);
    *store = NULL;
}

int store_insert(store_t *store, const uint8_t *key, size_t key_len, const uint8_t *value, size_t value_len)
{
    assert(store != NULL);
    assert(key != NULL);
    assert(key_len > 0);
    assert(value != NULL);
    assert(value_len > 0);

    // Copy the key and value into the store
    if (store->remaining < key_len + value_len)
    {
        return STORE_ERR_FULL;
    }
    memcpy(store->free, key, key_len);
    memcpy(store->free + key_len, value, value_len);

    // Create a key_value_t for the B-tree
    key_value_t kv;
    kv.key = store->free;
    kv.key_len = key_len;
    kv.val_len = value_len;

    if (btree_insert(store->index, (uint8_t *)&kv) != BTREE_ERR_OK)
    {
        return STORE_ERR_ALLOC;
    }
    store->free += key_len + value_len;
    store->remaining -= key_len + value_len;

    return STORE_ERR_OK;
}

uint8_t *store_search(const store_t *store, const uint8_t *key, size_t key_len, size_t *value_len)
{
    assert(store != NULL);
    assert(key != NULL);
    assert(key_len > 0);
    assert(value_len != NULL);

    key_value_t kv;
    kv.key = key;
    kv.key_len = key_len;

    const key_value_t *found_kv = (const key_value_t *)btree_search(store->index, (uint8_t *)&kv);

    if (found_kv == NULL)
    {
        return NULL;
    }

    *value_len = found_kv->val_len;
    return (uint8_t *)found_kv->key + found_kv->key_len; // Return pointer to the value in the store
}

void store_delete(store_t *store, const uint8_t *key, size_t key_len)
{
    assert(store != NULL);
    assert(key != NULL);
    assert(key_len > 0);

    key_value_t kv;
    kv.key = key;
    kv.key_len = key_len;

    btree_delete(store->index, (uint8_t *)&kv);
}
