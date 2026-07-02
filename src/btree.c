/**
 * @file b_tree.c
 *
 * @brief B-tree implementation
 *
 ***************************************************************************************************
 *  Simple B-tree implementation
 ***************************************************************************************************
 */

#include <stdbool.h> /* bool type */
#include <stddef.h>  /* NULL, size_t */
#include <stdlib.h>  /* malloc, free, EXIT_SUCCESS and EXIT_FAILURE */
#include <stdint.h>  /* uint8_t */
#include <string.h>  /* memmove, memset */
#include <assert.h>  /* assert */
#include <stdio.h>   /* printf */

#define DEBUG
#include "btree.h"

/**
 * @brief A node in the B-tree
 */
typedef struct _node
{
    size_t num_keys;         /* Number of keys in the node */
    uint8_t *keys;           /* Array of keys, use uint8_t not void** so we can do pointer arithmetic */
                             /* keys is an array of void *s */
    struct _node **children; /* Array of pointers to child nodes */
} node_t;

/**
 * @brief The B-tree
 */
struct _btree
{
    size_t t;               /* Minimum degree */
    size_t key_size;        /* Size of each key */
    node_t *root;           /* Root node */
    compare_func_t compare; /* Comparison function for key */
};

/*
 *   ----------------------------------------------
 *   | The node   | The key list | The child list |
 *   ----------------------------------------------
 *     key ---------^              ^
 *     Children -------------------^
 */

/**
 * @brief Create a new B-tree node
 *
 * @note Allocated the memory for the keys and, if not a leaf node, the children
 *
 * @param btree   The B-tree
 * @param is_leaf Whether the node is a leaf node
 *
 * @return the allocated node, NULL allocation failed
 */
static node_t *btree_node_alloc(const btree_t *btree, bool is_leaf)
{
    assert(btree != NULL);
    assert(btree->t > 1);
    assert(sizeof(node_t) % btree->key_size == 0);

    size_t keys_size = btree->key_size * ((2 * btree->t) - 1);
    node_t *node = (node_t *)malloc(sizeof(node_t) + keys_size + (is_leaf ? 0 : sizeof(node_t *) * (2 * btree->t)));
    if (node != NULL)
    {
        node->children = NULL;
        node->num_keys = 0;
        node->keys = (uint8_t *)(node) + sizeof(node_t);
        if (!is_leaf)
        {
            node->children = (node_t **)(node->keys + keys_size);
        }
        else
        {
            node->children = NULL;
        }
    }
    return node;
}

/**
 * @brief Free a B-tree node and all its descendants
 *
 * @note Frees the memory for the keys and, if not a leaf node, the children
 *
 * @param node The node to destroy
 */
static void btree_node_free(node_t *node)
{
    assert(node != NULL);
    assert(node->keys != NULL);
    free(node);
}

/**
 * @brief Determine if a B-tree node is a leaf
 *
 * @return true if the node is a leaf, false otherwise
 */
static inline bool node_is_leaf(const node_t *node)
{
    assert(node != NULL);
    return node->children == NULL;
}

/**
 * @brief free a B-tree node and all its descendants
 *
 * @note Frees the memory for the keys and, if not a leaf node, the children
 *
 * @param node  The node to destroy
 */
static void node_subtree_destroy(node_t *node)
{
    assert(node != NULL);
    assert(node->keys != NULL);

    if (!node_is_leaf(node))
    {
        for (size_t i = 0; i <= node->num_keys; i++)
        {
            node_subtree_destroy(node->children[i]);
        }
    }
    btree_node_free(node);
}

/**
 * @brief Get the address of the key from a B-tree node at a given index
 *
 * @param btree The B-tree
 * @param node The node to get the key from
 * @param index The index of the key to get
 *
 * @return A pointer to the key at the given index
 */
static inline uint8_t *btree_node_key_at(const btree_t *btree, const node_t *node, size_t index)
{
    assert(node != NULL);
    assert(node->keys != NULL);

    return node->keys + (index * btree->key_size);
}

/**
 * @brief Get an key from a B-tree node at a given index
 *
 * @param btree The B-tree
 * @param node The node to get the key from
 * @param index The index of the key to get
 *
 * @return The key at the given index
 */
static inline const void *btree_node_key(const btree_t *btree, const node_t *node, size_t index)
{
    assert(node != NULL);
    assert(index <= node->num_keys);

    return *(void **)btree_node_key_at(btree, node, index);
}

/**
 * @brief Move an key in to the node at index
 *
 * @note The current key at the index will be over written, space for the key should be made first
 *
 * @param btree      The B-tree
 * @param node_dest  The node to receive the key
 * @param index_dest The index of the key to get
 * @param key_src    The source key to put in to the node
 */
static inline void btree_node_move_key_at(const btree_t *btree, node_t *node_dest, size_t index_dest, const void *key_src)
{
    assert(node_dest != NULL);
    assert(index_dest <= node_dest->num_keys);
    assert(key_src != NULL);

    memcpy(btree_node_key_at(btree, node_dest, index_dest), &key_src, btree->key_size);
}

/**
 * @brief Move the keys to the right to make space fro a new keys
 *
 * @note only make space if the index is not at the end of the key list.
 *
 * @param node  The node with the keys
 * @param index The index of the key to move
 */
static void btree_node_move_keys_right(const btree_t *btree, node_t *node, size_t index)
{
    assert(node != NULL);
    assert(index <= node->num_keys);

    if (index < node->num_keys)
    {
        // Shift the keys of the parent to make room for the key coming up form the child
        memmove(btree_node_key_at(btree, node, index + 1), btree_node_key_at(btree, node, index), (node->num_keys - index) * btree->key_size);
    }
}

/**
 * @brief Split a child node of the B-tree
 *
 * @note Split the child node at index, and move the middle key to the partent
 *
 *  Before                 After
 *   node, index=1, t=2
 *   {   3   }              {   3    5   }
 *     V   V                V     V    V
 *{ 1 2 }  { 4 5 6 }   { 1 2 }  { 4 }  { 5 }
 *
 * @param btree  The B-tree
 * @param parent The parent node
 * @param index  The index of the child node to split
 *
 * @return BTREE_ERR_OK if successful, BTREE_ERR_ALLOC if memory allocation fails
 */
static int btree_node_split_child(const btree_t *btree, node_t *parent, size_t index)
{
    assert(btree != NULL);
    assert(parent != NULL);
    assert(index <= parent->num_keys);
    assert(parent->num_keys >= (btree->t - 1) || parent == btree->root);
    assert(parent->num_keys <= ((btree->t * 2) - 1));
    assert(parent->children[index]->num_keys == ((btree->t * 2) - 1));

    size_t t = btree->t;
    // Get the child node to split
    node_t *child = parent->children[index];

    node_t *new_child = btree_node_alloc(btree, node_is_leaf(child));
    if (new_child == NULL)
    {
        fprintf(stderr, "Failed to create new child node\n");
        return BTREE_ERR_ALLOC;
    }

    // Move the second half of the keys to the new child
    memcpy(new_child->keys, btree_node_key_at(btree, child, t), btree->key_size * t);

    if (!node_is_leaf(child))
    {
        // Move the second half of the children to the new child
        memcpy(&new_child->children[0], &child->children[t], sizeof(node_t *) * t);
    }
    // Update the number of keys in the new child
    new_child->num_keys = t - 1;

    // Update the number of keys in the original child
    child->num_keys = t - 1;

    // Shift the keys of the parent to make room for the key coming up form the child
    btree_node_move_keys_right(btree, parent, index);

    // Move the median key from the child to the parent
    btree_node_move_key_at(btree, parent, index, btree_node_key(btree, child, t - 1));

    if (index < parent->num_keys)
    {
        // Shift the children of the parent to make room for the new child
        memmove(&parent->children[index + 2], &parent->children[index + 1], (parent->num_keys - index) * sizeof(node_t *));
    }
    // Insert the new child into the parent
    parent->children[index + 1] = new_child;
    parent->num_keys++;

    return BTREE_ERR_OK;
}

/**
 * @brief Split the root of the B-tree
 *
 * @note create a new root, with the middel key and two child nodes with the left and right nodes
 *
 * Before                     After
 * Root, t=3
 * [5 6 7 8 9]              [7]
 *                     [5 6]   [8  9]
 *
 * @param btree The B-tree
 *
 * @return BTREE_ERR_OK if successful, BTREE_ERR_ALLOC if memory allocation fails
 */
static int btree_split_root(btree_t *btree)
{
    assert(btree != NULL);

    // Create a new root node the space for keys and children
    node_t *new_root = btree_node_alloc(btree, false);
    if (new_root == NULL)
    {
        fprintf(stderr, "Failed to create new root node\n");
        return BTREE_ERR_ALLOC;
    }

    // Move the old root to be the first child of the new root
    new_root->children[0] = btree->root;

    // Put the new root in the btree root
    btree->root = new_root;

    // Split the old root in two and move them  middle key up to the new root
    if (btree_node_split_child(btree, btree->root, 0) != BTREE_ERR_OK)
    {
        fprintf(stderr, "Failed to split root node\n");
        return BTREE_ERR_ALLOC;
    }
    return BTREE_ERR_OK;
}

/**
 * @brief Reduce the hight oF the btree
 *
 * @note The root should have no key and one child, the child may have children
 *
 * Before                   After
 * Root, t=3
 * []                      [5 6 7 8 9]
 * [5 6 7 8 9]
 *
 * @param btree The B-tree
 *
 */
static void btree_move_root_up(btree_t *btree)
{
    assert(btree != NULL);
    assert(btree->root->num_keys == 0);
    assert(btree->root->keys != NULL);
    assert(btree->root->children != NULL);
    assert(btree->root->children[0]->num_keys > 0);
    assert(btree->root->children[0]->keys != NULL);

    node_t *old_root = btree->root;
    btree->root = old_root->children[0];

    btree_node_free(old_root);
}

/**
 * @brief determine if a B-tree node is full
 *
 * @param btree The B-tree
 * @param node The node to check
 *
 * @return true if the node is full, false otherwise
 */
static inline bool btree_node_is_full(const btree_t *btree, const node_t *node)
{
    assert(btree != NULL);
    assert(node != NULL);
    assert(node->num_keys >= (btree->t - 1) || node == btree->root);
    assert(node->num_keys <= ((btree->t * 2) - 1));

    return node->num_keys == ((2 * btree->t) - 1);
}

/**
 * @brief Insert a key into the subtree rooted at node, which is assumed
 *        to be not full
 *
 * @param btree The B-tree
 * @param node  The root of the subtree to insert into
 * @param key   The key to insert
 *
 * @return BTREE_ERR_OK if successful, BTREE_ERR_ALLOC if memory allocation fails
 */
static int btree_node_insert_not_full(btree_t *btree, node_t *node, const void *key)
{
    assert(btree != NULL);
    assert(node != NULL);
    assert(key != NULL);
    assert(node->num_keys < ((btree->t * 2) - 1));
    assert(node->num_keys >= (btree->t - 1) || node == btree->root);

    // Find the index to insert the new key
    size_t index = 0;
    // While index is lessthan the numbers of keys and key is greaterthan the current of key
    int comp = -1;
    while (index < node->num_keys)
    {
        comp = btree->compare(key, btree_node_key(btree, node, index));
        if (comp <= 0)
        {
            // The key is not greaterthan the current key
            break;
        }
        index++;
    }
    // Found the key, so replace the key
    if (comp == 0)
    {
        btree_node_move_key_at(btree, node, index, key);
    }
    else
    {
        if (node_is_leaf(node))
        {
            // Shift the keys of the node to make room for the key
            btree_node_move_keys_right(btree, node, index);
            // Move the key in to the node
            btree_node_move_key_at(btree, node, index, key);
            node->num_keys++;
        }
        else
        {
            // If the child is full, split it
            if (btree_node_is_full(btree, node->children[index]))
            {
                if (btree_node_split_child(btree, node, index) != BTREE_ERR_OK)
                {
                    fprintf(stderr, "Failed to split child node\n");
                    return BTREE_ERR_ALLOC;
                }
                if (btree->compare(key, btree_node_key(btree, node, index)) > 0)
                {
                    index++;
                }
            }
            if (btree_node_insert_not_full(btree, node->children[index], key) != BTREE_ERR_OK)
            {
                fprintf(stderr, "Failed to insert key into subtree\n");
                return BTREE_ERR_ALLOC;
            }
        }
    }
    return BTREE_ERR_OK;
}

/**
 * @brief Search the sub tree for the key
 *
 * @param btree The B-tree
 * @param node  The root of the subtree to insert into
 * @param key   The key to search
 *
 * @return the key found, ot NULL, key not found
 */
static const void *btree_node_search(const btree_t *btree, const node_t *node, const void *key)
{
    assert(btree != NULL);
    assert(node != NULL);
    assert(key != NULL);
    assert(node->num_keys >= (btree->t - 1) || node == btree->root);

    size_t index = 0;
    // while the index lessthan the number of keys and the key is greaterthan the current key
    while (index < node->num_keys)
    {
        int comp = btree->compare(key, btree_node_key(btree, node, index));
        if (comp == 0)
        {
            // Found the key
            return btree_node_key(btree, node, index);
        }
        else if (comp < 0)
        {
            // The Key is not greaterthan the current key
            break;
        }
        index++;
    }
    if (node_is_leaf(node))
    {
        return NULL;
    }
    return btree_node_search(btree, node->children[index], key);
}

/**
 * @brief Merge the children of parent at index and index+1.
 *
 * @note Both nodes should have t-1 keys,
 *
 *   Before             After
 *     node, Index = 0
 *     [2    4]               [4]
 *   [1]  [3] [5 6]     [1 2 3]  [5 6]
 *
 * @param btree  The B-tree
 * @param parent The node with children to merge
 * @param index  The index of the first child to merge
 */
static void btree_node_merge_children(btree_t *btree, node_t *parent, size_t index)
{
    assert(btree != NULL);
    assert(parent != NULL);
    assert(index < parent->num_keys);
    assert(parent->num_keys >= (btree->t - 1) || parent == btree->root);
    assert(parent->children[index]->num_keys <= btree->t - 1);
    assert(parent->children[index + 1]->num_keys <= btree->t - 1);

    // Get the key that we are moving down
    const void *median_key = btree_node_key(btree, parent, index);

    node_t *left_child = parent->children[index];
    node_t *right_child = parent->children[index + 1];

    // Put the median_key in to the end of the left child
    btree_node_move_key_at(btree, left_child, left_child->num_keys, median_key);
    left_child->num_keys++;

    // Add the keys from the right child
    memmove(btree_node_key_at(btree, left_child, left_child->num_keys),
            btree_node_key_at(btree, right_child, 0),
            right_child->num_keys * btree->key_size);

    // If there are grand children, copy them
    if (!node_is_leaf(left_child))
    {
        memmove(&left_child->children[left_child->num_keys],
                &right_child->children[0],
                (right_child->num_keys + 1) * sizeof(node_t *));
    }
    left_child->num_keys += right_child->num_keys;

    // Free the righthand child
    btree_node_free(right_child);

    // Remove the key at index from the node, and the righthand child
    if (index < parent->num_keys)
    {
        memmove(btree_node_key_at(btree, parent, index),
                btree_node_key_at(btree, parent, index + 1),
                (parent->num_keys - index) * btree->key_size);
        memmove(&parent->children[index + 1],
                &parent->children[index + 2],
                (parent->num_keys - index) * sizeof(node_t *));
    }
    parent->num_keys--;
}

/**
 * @brief Rotate the keys anticlockwise
 *
 * @note Move the key at index to the end of the lift child
 *       move the first key from the right child in to the node at index
 *
 *  Before               After
 *     node, Index = 0
 *    [6    9]               [7   9]
 *  [5] [78] [10 11]     [5 6] [8] [10 11]
 *
 * @param btree  The B-tree
 * @param parent The node with children rotate
 * @param index  The index of the key to rotate
 */
static void btree_node_rotate_anticlockwise(btree_t *btree, node_t *parent, size_t index)
{
    assert(btree != NULL);
    assert(parent != NULL);
    assert(index < parent->num_keys);
    assert(parent->num_keys >= (btree->t - 1) || parent == btree->root);
    assert(parent->children[index]->num_keys <= (btree->t - 1));
    assert(parent->children[index + 1]->num_keys >= (btree->t - 1));

    // Get the key that we are moving down
    const void *key = btree_node_key(btree, parent, index);

    node_t *left_child = parent->children[index];
    node_t *right_child = parent->children[index + 1];

    // Move the fist key from the right child to the parent node
    btree_node_move_key_at(btree, parent, index, btree_node_key(btree, right_child, 0));

    // Delete the first key from the right child
    memmove(btree_node_key_at(btree, right_child, 0), btree_node_key_at(btree, right_child, 1), right_child->num_keys * btree->key_size);

    // Put the key in the end of the left child
    btree_node_move_key_at(btree, left_child, left_child->num_keys, key);

    // Move the grand children if the child is not a leaf
    if (!node_is_leaf(left_child))
    {
        // Move the first right child to the last left child
        left_child->children[left_child->num_keys + 1] = right_child->children[0];
        // Delete the fist right child
        memmove(&right_child->children[0], &right_child->children[1], (right_child->num_keys) * sizeof(node_t *));
    }
    right_child->num_keys--;
    left_child->num_keys++;
}

/**
 * @brief Rotate the keys clockwise
 *
 * @note Move the key at index to the start of the right child
 *       move the last key from the left child in to the node at index
 *
 *     Before                    After
 *     node, Index = 0
 *      [7   9]               [6     9]
 *  [5 6] [8] [10 11]       [5] [7 8] [10 11]
 *
 * @param btree  The B-tree
 * @param parent The node with children to rotate
 * @param index  The index of the key to rotate
 */
static void btree_node_rotate_clockwise(btree_t *btree, node_t *parent, size_t index)
{
    assert(btree != NULL);
    assert(parent != NULL);
    assert(index < parent->num_keys);
    assert(parent->num_keys >= (btree->t - 1) || parent == btree->root);
    assert(parent->children[index]->num_keys >= (btree->t - 1));
    assert(parent->children[index + 1]->num_keys <= (btree->t - 1));

    // Get the key that we are moving down
    const void *key = btree_node_key(btree, parent, index);

    node_t *left_child = parent->children[index];
    node_t *right_child = parent->children[index + 1];

    // Move the last key from the left child to the parent node
    btree_node_move_key_at(btree, parent, index, btree_node_key(btree, left_child, left_child->num_keys - 1));

    // Move the partent key to the fist key of the right child
    btree_node_move_keys_right(btree, right_child, 0);
    btree_node_move_key_at(btree, right_child, 0, key);

    // Move the grand children if the child is not a leaf
    if (!node_is_leaf(right_child))
    {
        // Move the children in the righthand child right to make space
        memmove(&right_child->children[1], &right_child->children[0], (right_child->num_keys + 1) * sizeof(node_t *));
        // Move over the last left children to the first right first children
        right_child->children[0] = left_child->children[left_child->num_keys];
    }
    left_child->num_keys--;
    right_child->num_keys++;
}

/**
 * @brief Delete the key in the sub tree
 *
 * @param btree The B-tree
 * @param node  The root of the subtree to insert into
 * @param key   The key to search
 */
void btree_node_delete(btree_t *btree, node_t *node, const uint8_t *key)
{
    assert(btree != NULL);
    assert(node != NULL);
    assert(node->num_keys >= (btree->t - 1) || node == btree->root);
    assert(node->num_keys <= ((btree->t * 2) - 1));

    // Find the index to insert the new key
    size_t index = 0;
    int comp = -1;
    while (index < node->num_keys)
    {
        comp = btree->compare(key, btree_node_key(btree, node, index));
        if (comp <= 0)
        {
            // The key is not greaterthan the current key
            break;
        }
        index++;
    }

    if (node_is_leaf(node))
    {
        if (index < node->num_keys && comp == 0)
        {
            // Case 1 we have found the key in a leaf node
            // Delete the key from the leaf node
            memmove(btree_node_key_at(btree, node, index), btree_node_key_at(btree, node, index + 1), (node->num_keys - index) * btree->key_size);
            node->num_keys--;
        }
        return;
    }

    if (index < node->num_keys && comp == 0)
    {
        // Case 2 we have found the key in a node with children
        if (node->children[index]->num_keys >= btree->t)
        {
            // Case 2a - the left node has >= t nodes, so we can move the predecessor up from the child
            //           and replace the node the we are deleteing
            // Get the predecessor key (most right key form the child node with index)
            node_t *pred_node = node->children[index];
            while (!node_is_leaf(pred_node))
            {
                pred_node = pred_node->children[pred_node->num_keys];
            }
            const void *pred_key = btree_node_key(btree, pred_node, pred_node->num_keys - 1);

            // Delete the predecessor key, from the predecessor node
            btree_node_delete(btree, node->children[index], pred_key);

            // replace the key to be deleted with the predecessor form the chiles
            btree_node_move_key_at(btree, node, index, pred_key);
            return;
        }
        else if (node->children[index + 1]->num_keys >= btree->t)
        {
            // Case 2b - the right node has >= t nodes, so we can move the successor up from the child
            //           and replace the node the we are deleteing
            // We can bing the last key up from the right node
            // Get the successor key (most left key form the child node with index+1)
            node_t *succ_node = node->children[index + 1];
            while (!node_is_leaf(succ_node))
            {
                succ_node = succ_node->children[0];
            }
            const void *succ_key = btree_node_key(btree, succ_node, 0);

            // Delete the successor key, from the successor node
            btree_node_delete(btree, node->children[index + 1], succ_key);

            // replace the key to be deleted with the predecessor form the chiles
            btree_node_move_key_at(btree, node, index, succ_key);
            return;
        }
        else
        {
            // Case 2c, both children have t-1 keys, we can not delete an node in iether one
            //          So merge the two children and move the key at index down.
            //          This may remove the last key in the root, in this case make the root
            //          the first child node, this reduces the hight og the key
            // Merge the children and move down the key at the index
            btree_node_merge_children(btree, node, index);
            if (node == btree->root && node->num_keys == 0)
            {
                // The merge move the last key in the root, reduce the hight
                btree_move_root_up(btree);
                // Delete the key from the root
                btree_node_delete(btree, btree->root, key);
                return;
            }
            btree_node_delete(btree, node->children[index], key);
            return;
        }
    }
    // Case 3 key not in node, so look in the child
    //        If there is at least t keys in the child, we can just call delete on the child
    //        else we need to deal with the sub cases
    if (node->children[index]->num_keys < btree->t)
    {
        if ((index > 0) && node->children[index - 1]->num_keys >= btree->t)
        {
            // Case 3al - the left sibling hash at lest t keys
            btree_node_rotate_clockwise(btree, node, index - 1);
        }
        else if ((index < node->num_keys) && node->children[index + 1]->num_keys >= btree->t)
        {
            // Case 3ar - the right sibling hash at lest t keys
            btree_node_rotate_anticlockwise(btree, node, index);
        }
        else
        {
            // case 3b node is not a leaf and both siblings have t-1 keys
            if (index > 0)
            {
                // Case 3bl: We merge with left sibling,
                //           The merge will move the key at index down to the child
                btree_node_merge_children(btree, node, index - 1);
                index--; // we now have one less child, so we shift over
            }
            else
            {
                // Case 3br: We merge with right sibling,
                //           The merge will move the key at index down to the child
                btree_node_merge_children(btree, node, index);
            }
            if (node == btree->root && node->num_keys == 0)
            {
                // The merge move the last key in the root, reduce the hight
                btree_move_root_up(btree);

                // Delete the key from the root
                btree_node_delete(btree, btree->root, key);
                return;
            }
        }
    }
    btree_node_delete(btree, node->children[index], key);
}

#ifdef DEBUG
// /**
//  * @brief Print the B-tree node and sub tree
//  *
//  * @param node       The node to print
//  * @param print_func The function to use for printing keys
//  */
// void btree_node_keys_print(const node_t *node, print_func_t print_func)
// {
//     assert(node != NULL);
//     assert(print_func != NULL);
//     printf("[");
//     for (size_t i = 0; i < node->num_keys; i++)
//     {
//         print_func(btree_node_key(node, i));
//         if (i < node->num_keys - 1)
//         {
//             printf(", ");
//         }
//     }
//     printf("] ");
// }

// /**
//  * @brief Print the B-tree node and sub tree
//  *
//  * @param btree      The B-tree to print
//  * @param level      The level in the tree
//  * @param node       The node to print
//  * @param print_func The function to use for printing keys
//  */
// void btree_node_print(const size_t level, const node_t *node, print_func_t print_func)
// {
//     assert(node != NULL);
//     assert(print_func != NULL);

//     printf("%zu", level);
//     btree_node_keys_print(node, print_func);
//     fflush(stdout);

//     if (!node_is_leaf(node))
//     {
//         printf("\n");
//         for (size_t i = 0; i <= node->num_keys; i++)
//         {
//             btree_node_print(level + 1, node->children[i], print_func);
//         }
//         printf("\n");
//     }
// }

// void debug_key_print(const void *key)
// {
//     printf("%s", (char *)key);
// }

// void debug_node_print(const node_t *node)
// {
//     btree_node_print(0, node, &debug_key_print);
//     printf("\n");
// }

// void debug_node_keys_print(const node_t *node)
// {
//     btree_node_keys_print(node, &debug_key_print);
//     printf("\n");
// }

/**
 * @brief Validate that all the keys in the right tree are more then the max value
 *
 * @param btree   The B-tree to print
 * @param node    The node to validate
 * @param min     The minimum value in the node
 *
 * @return true, the tree is valid. false, the tree is not valid
 */
bool btree_node_validate_right_tree(const btree_t *btree, const node_t *node, const void *min)
{
    for (size_t index = 0; index < node->num_keys; index++)
    {
        const void *key = btree_node_key(btree, node, index);
        if (btree->compare(key, min) < 0)
        {
            return false;
        }
    }
    if (!node_is_leaf(node))
    {
        for (size_t index = 0; index <= node->num_keys; index++)
        {
            if (!btree_node_validate_right_tree(btree, node->children[index], min))
            {
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief Validate that all the keys in the sum tree are less then the max value
 *
 * @param btree   The B-tree to print
 * @param node    The node to validate
 * @param max     The maximum value in the node
 *
 * @return true, the tree is valid. false, the tree is not valid
 */
bool btree_node_validate_left_tree(const btree_t *btree, const node_t *node, const void *max)
{
    for (size_t index = 0; index < node->num_keys; index++)
    {
        const void *key = btree_node_key(btree, node, index);
        if (btree->compare(key, max) > 0)
        {
            return false;
        }
    }
    if (!node_is_leaf(node))
    {
        for (size_t index = 0; index <= node->num_keys; index++)
        {
            if (!btree_node_validate_left_tree(btree, node->children[index], max))
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Validate that all the keys in the tree are less then the max value
 *
 * @param btree   The B-tree to print
 * @param node    The node to validate
 * @param max     The maximum value in the node
 *
 * @return true, the tree is valid. false, the tree is not valid
 */
bool btree_node_validate(const btree_t *btree, const node_t *node)
{
    if ((node->keys == NULL) ||
        (node->num_keys < (btree->t - 1) && node != btree->root) ||
        (node->num_keys > ((btree->t * 2) - 1)))
    {
        return false;
    }

    for (size_t index = 0; index < node->num_keys; index++)
    {
        const void *key = btree_node_key(btree, node, index);
        if (index < node->num_keys - 1)
        {
            const void *next = btree_node_key(btree, node, index + 1);
            if (btree->compare(key, next) > 0)
            {
                return false;
            }
        }
        if (!node_is_leaf(node))
        {
            if (!btree_node_validate_left_tree(btree, node->children[index], key))
            {
                return false;
            }
            if (!btree_node_validate_right_tree(btree, node->children[index + 1], key))
            {
                return false;
            }
        }
    }
    if (!node_is_leaf(node))
    {
        for (size_t index = 0; index <= node->num_keys; index++)
        {
            btree_node_validate(btree, node->children[index]);
        }
    }
    return true;
}
#endif

/**************************************************************************************************
 * The API
 *************************************************************************************************/

int btree_insert(btree_t *btree, const uint8_t *key)
{
    assert(btree != NULL);
    assert(key != NULL);

    if (btree_node_is_full(btree, btree->root))
    {
        if (btree_split_root(btree) != BTREE_ERR_OK)
        {
            fprintf(stderr, "Failed to split root node\n");
            return BTREE_ERR_ALLOC;
        }
    }
    if (btree_node_insert_not_full(btree, btree->root, key) != BTREE_ERR_OK)
    {
        fprintf(stderr, "Failed to insert key into tree\n");
        return BTREE_ERR_ALLOC;
    }
    return BTREE_ERR_OK;
}

const void *btree_search(const btree_t *btree, const uint8_t *key)
{
    return btree_node_search(btree, btree->root, key);
}

void btree_delete(btree_t *btree, const uint8_t *key)
{
    btree_node_delete(btree, btree->root, key);
}

btree_t *btree_init(const size_t t, const size_t key_size, const compare_func_t compare)
{
    assert(compare != NULL);

    btree_t *btree = (btree_t *)malloc(sizeof(btree_t));
    if (btree)
    {
        btree->t = t;
        btree->key_size = key_size;
        btree->compare = compare;
        btree->root = btree_node_alloc(btree, true);
        if (btree->root != NULL)
        {
            return btree;
        }
        else
        {
            free(btree);
            btree = NULL;
        }
    }
    return NULL;
}

void btree_deinit(btree_t **btree)
{
    assert(btree != NULL);
    assert(*btree != NULL);

    node_subtree_destroy((*btree)->root);
    free(*btree);
    *btree = NULL;
}

#ifdef DEBUG
// void btree_print(const btree_t *btree, print_func_t print_func)
// {
//     assert(btree != NULL);
//     assert(print_func != NULL);

//     btree_node_print(0, btree->root, print_func);
//     printf("\n");
// }

bool btree_validate(const btree_t *btree)
{
    return btree_node_validate(btree, btree->root);
}
#endif
