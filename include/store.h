/**
 * @file store.h
 *
 * @brief simple store using a B-tree implementation
 *
 ***************************************************************************************************
 *
 **************************************************************************************************/
#pragma once

#if defined(__cplusplus)
extern "C"
{
#endif

    /**
     *  @brief the store
     */
    typedef struct _store store_t;

    /**
     * @brief Initialize the store
     *
     * @param pages The number of pages to allocate for the store
     *
     * @return the store, NULL allocation failed
     */
    store_t *store_init(size_t pages);

    /**
     * @brief De-initialize the store
     *
     * @param store The store to de-initialize
     */
    void store_deinit(store_t **store);

    /**
     * @brief Insert a key and value into the store
     *
     * @param store     The store to insert into
     * @param key       The key to insert
     * @param key_len   The length of the key
     * @param value     The value to insert
     * @param value_len The length of the value
     *
     * @return EXIT_SUCCESS if successful, EXIT_FAILURE if an error occurred
     */
    int store_insert(store_t *store, const uint8_t *key, size_t key_len, const uint8_t *value, size_t value_len);

    /**
     * @brief Search for a key in the store
     *
     * @param store           The store to search
     * @param key             The key to search for
     * @param key_len         The length of the key
     * @param [out] value_len The length of the value found, or 0 if not found
     *
     * @return The value found, or NULL if not found.
     */
    uint8_t *store_search(const store_t *store, const uint8_t *key, size_t key_len, size_t *value_len);

    /**
     * @brief Delete a key and its value from the store
     *
     * @param store     The store to delete from
     * @param key       The key to delete
     * @param key_len   The length of the key
     */
    void store_delete(store_t *store, const uint8_t *key, size_t key_len);

#ifdef __cplusplus
}
#endif
