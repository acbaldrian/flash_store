/**
 * @file b_tree.h
 *
 * @brief B-tree implementation
 *
 ***************************************************************************************************
 * Simple B-tree implementation
 *
 * The key objects are copied into the B-tree.
 * Memory for all the keys in a node is allocated for each node.
 * A pointer to the key is returned by the search function.
 * When the B-tree is de-initialized, the memory for all the memory for the keys in the node is freed.
 *
 **************************************************************************************************/
#pragma once

#if defined(__cplusplus)
extern "C"
{
#endif

#ifdef DEBUG
#include <stdbool.h>
#endif

#define BTREE_ERR_OK (0)     /* Return value for successful operations */
#define BTREE_ERR_ALLOC (-1) /* Return value for memory allocation failures */

    /**
     *  @brief The B-tree
     */
    typedef struct _btree btree_t;

    /**
     * @brief Comparison function prototype for keys in the B-tree.
     *
     * @param lh Left-hand side key
     * @param rh Right-hand side key
     *
     * @return Negative value if lh < rh, zero if lh == rh, positive value if lh > rh
     */
    typedef int (*compare_func_t)(const void *lh, const void *rh);

    /**
     * @brief Insert a new key into the B-tree
     *
     * @note If the same key exist in the btree it is replaced
     *
     * @param btree The B-tree
     * @param key   Pointer to the ket object to insert
     *
     * @return BTREE_ERR_OK if successful, BTREE_ERR_ALLOC if memory allocation fails
     */
    int btree_insert(btree_t *btree, const uint8_t *key);

    /**
     * @brief Find the key in the btree
     *
     * @param btree The B-tree
     * @param key   Pointer to the key object to search for
     *
     * @return Pointer to the key found, or NULL if key not found
     */
    const void *btree_search(const btree_t *btree, const uint8_t *key);

    /**
     * @brief Delete the key with the key
     *
     * @param btree The B-tree
     * @param key   Pointer to the key object to delete
     */
    void btree_delete(btree_t *btree, const uint8_t *key);

    /**
     * @brief Initialise a B-tree
     *
     * @param t        The minimum degree of the B-tree
     * @param key_size The size of each key
     * @param compare  The comparison function for keys in the B-tree
     *
     * @return The B-tree, NULL allocation failed
     */
    btree_t *btree_init(const size_t t, const size_t key_size, const compare_func_t compare);

    /**
     * @brief De-initialise a B-tree
     *
     * @param btree The B-tree to de-initialise
     */
    void btree_deinit(btree_t **btree);

#ifdef DEBUG

    // /**
    //  * @brief function prototype for a print function for keys in the B-tree.
    //  *
    //  * @param value The key to print
    //  */
    // typedef void (*print_func_t)(const void *value);

    // /**
    //  * @brief Print the B-tree
    //  *
    //  * @param btree The B-tree to print
    //  * @param print_func The function to use for printing keys
    //  */
    // void btree_print(const btree_t *btree, print_func_t print_func);

    /**
     * @brief Validate the tree
     *
     * @param btree The B-tree to print
     *
     * @return true, the tree is valid. false, the tree is not valid
     */
    bool btree_validate(const btree_t *btree);

#endif

#ifdef __cplusplus
}
#endif
