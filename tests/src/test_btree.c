#include <string.h>
#include <stdlib.h> //  EXIT_SUCCESS and EXIT_FAILURE
#include "unity.h"

#define DEBUG
#include "btree.h"

/**
 * @brief mock comparison function for testing
 *
 * @param lh Left-hand side item
 * @param rh Right-hand side item
 *
 * @return Negative value if lh < rh, zero if lh == rh, positive value if lh > rh
 */
static int mock_item_compare(const void *lh, const void *rh)
{
    char *left = (char *)lh;
    char *right = (char *)rh;
    return strcmp(left, right);
}

/**
 * @brief Create a B-tree, check that it is not NULL, and then de-initialize it
 */
static void test_init(void)
{
    btree_t *btree = btree_init(2, sizeof(char *), &mock_item_compare);
    TEST_ASSERT_NOT_NULL(btree);

    // De-initialize the B-tree
    btree_deinit(&btree);
    TEST_ASSERT_NULL(btree);
}

/**
 * @brief Insert an item into a B-tree, check that it is not NULL, and then de-initialize it
 */
static void test_insert(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";

    // Insert an item into the B-tree
    btree_insert(btree, (void *)exp_str_01);

    char *act_str_01 = (char *)btree_search(btree, (void *)"01");
    TEST_ASSERT_EQUAL(act_str_01, exp_str_01);
    TEST_ASSERT_EQUAL_STRING(act_str_01, exp_str_01);

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Insert an item into a B-tree, check that it is not NULL, and then de-initialize it
 */
static void test_fill_root_node(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));

    char *act_str_01 = (char *)btree_search(btree, (void *)"01");
    TEST_ASSERT_EQUAL(act_str_01, exp_str_01);
    TEST_ASSERT_EQUAL_STRING(act_str_01, exp_str_01);
    char *act_str_02 = (char *)btree_search(btree, (void *)"02");
    TEST_ASSERT_EQUAL(act_str_02, exp_str_02);
    TEST_ASSERT_EQUAL_STRING(act_str_02, exp_str_02);
    char *act_str_03 = (char *)btree_search(btree, (void *)"03");
    TEST_ASSERT_EQUAL(act_str_03, exp_str_03);
    TEST_ASSERT_EQUAL_STRING(act_str_03, exp_str_03);
    char *act_str_04 = (char *)btree_search(btree, (void *)"04");
    TEST_ASSERT_EQUAL(act_str_04, exp_str_04);
    TEST_ASSERT_EQUAL_STRING(act_str_04, exp_str_04);
    char *act_str_05 = (char *)btree_search(btree, (void *)"05");
    TEST_ASSERT_EQUAL(act_str_05, exp_str_05);
    TEST_ASSERT_EQUAL_STRING(act_str_05, exp_str_05);
    char *act_str_06 = (char *)btree_search(btree, (void *)"06");
    TEST_ASSERT_EQUAL(act_str_06, exp_str_06);
    TEST_ASSERT_EQUAL_STRING(act_str_06, exp_str_06);

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Insert an item into a B-tree, check that it is not NULL, and then de-initialize it
 *
 *        0[03,      06,        09]
 * 1[01, 02] 1[04, 05] 1[07, 08] 1[10, 11, 12]
 *
 */
static void test_simple_tree(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));

    char *act_str_01 = (char *)btree_search(btree, (void *)"01");
    TEST_ASSERT_EQUAL(act_str_01, exp_str_01);
    char *act_str_02 = (char *)btree_search(btree, (void *)"02");
    TEST_ASSERT_EQUAL(act_str_02, exp_str_02);
    char *act_str_03 = (char *)btree_search(btree, (void *)"03");
    TEST_ASSERT_EQUAL(act_str_03, exp_str_03);
    char *act_str_04 = (char *)btree_search(btree, (void *)"04");
    TEST_ASSERT_EQUAL(act_str_04, exp_str_04);
    char *act_str_05 = (char *)btree_search(btree, (void *)"05");
    TEST_ASSERT_EQUAL(act_str_05, exp_str_05);
    char *act_str_06 = (char *)btree_search(btree, (void *)"06");
    TEST_ASSERT_EQUAL(act_str_06, exp_str_06);
    char *act_str_07 = (char *)btree_search(btree, (void *)"07");
    TEST_ASSERT_EQUAL(act_str_07, exp_str_07);
    char *act_str_08 = (char *)btree_search(btree, (void *)"08");
    TEST_ASSERT_EQUAL(act_str_08, exp_str_08);
    char *act_str_09 = (char *)btree_search(btree, (void *)"09");
    TEST_ASSERT_EQUAL(act_str_09, exp_str_09);
    char *act_str_10 = (char *)btree_search(btree, (void *)"10");
    TEST_ASSERT_EQUAL(act_str_10, exp_str_10);
    char *act_str_11 = (char *)btree_search(btree, (void *)"11");
    TEST_ASSERT_EQUAL(act_str_11, exp_str_11);
    char *act_str_12 = (char *)btree_search(btree, (void *)"12");
    TEST_ASSERT_EQUAL(act_str_12, exp_str_12);

    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Insert an item into a B-tree, check that it is not NULL, and then de-initialize it
 */
static void test_insert_random(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"019"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"091"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"080"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"187"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"134"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"130"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"092"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"085"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"183"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"177"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"075"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"034"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"030"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"007"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"122"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"164"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"008"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"196"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"015"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"063"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"038"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"013"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"047"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"026"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"153"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"166"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"022"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"076"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"121"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"070"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"043"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"181"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"159"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"120"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"154"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"052"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"010"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"110"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"042"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"114"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"078"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"156"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"061"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"107"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"172"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"182"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"193"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"168"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"104"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"065"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"112"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"088"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"035"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"188"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"186"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"046"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"132"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"097"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"102"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"129"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"049"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"028"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"001"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"139"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"025"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"178"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"017"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"050"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"004"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"103"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"012"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"041"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"138"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"024"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"174"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"192"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"128"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"027"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"059"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"131"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"119"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"057"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"106"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"173"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"069"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"152"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"136"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"044"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"141"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"066"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"170"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"086"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"039"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"032"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"077"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"064"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"126"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"056"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"006"));

    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Insert an item into a B-tree, check that it is not NULL, and then de-initialize it
 */
static void test_search(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));

    char *act_str_01 = (char *)btree_search(btree, (void *)"01");
    TEST_ASSERT_EQUAL_STRING(act_str_01, exp_str_01);
    char *act_str_02 = (char *)btree_search(btree, (void *)"02");
    TEST_ASSERT_EQUAL_STRING(act_str_02, exp_str_02);
    char *act_str_03 = (char *)btree_search(btree, (void *)"03");
    TEST_ASSERT_EQUAL_STRING(act_str_03, exp_str_03);
    char *act_str_04 = (char *)btree_search(btree, (void *)"04");
    TEST_ASSERT_EQUAL_STRING(act_str_04, exp_str_04);
    char *act_str_05 = (char *)btree_search(btree, (void *)"05");
    TEST_ASSERT_EQUAL_STRING(act_str_05, exp_str_05);
    char *act_str_06 = (char *)btree_search(btree, (void *)"06");
    TEST_ASSERT_EQUAL_STRING(act_str_06, exp_str_06);
    char *act_str_07 = (char *)btree_search(btree, (void *)"07");
    TEST_ASSERT_EQUAL_STRING(act_str_07, exp_str_07);
    char *act_str_08 = (char *)btree_search(btree, (void *)"08");
    TEST_ASSERT_EQUAL_STRING(act_str_08, exp_str_08);
    char *act_str_09 = (char *)btree_search(btree, (void *)"09");
    TEST_ASSERT_EQUAL_STRING(act_str_09, exp_str_09);
    char *act_str_10 = (char *)btree_search(btree, (void *)"10");
    TEST_ASSERT_EQUAL_STRING(act_str_10, exp_str_10);
    char *act_str_11 = (char *)btree_search(btree, (void *)"11");
    TEST_ASSERT_EQUAL_STRING(act_str_11, exp_str_11);
    char *act_str_12 = (char *)btree_search(btree, (void *)"12");
    TEST_ASSERT_EQUAL_STRING(act_str_12, exp_str_12);
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Insert an item into a B-tree, search for the item, and then de-initialize it
 */
static void test_search_random_order(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"019"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"091"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"080"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"187"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"134"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"130"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"092"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"085"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"183"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"177"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"075"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"034"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"030"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"007"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"122"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"164"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"008"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"196"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"015"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"063"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"038"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"013"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"047"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"026"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"153"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"166"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"022"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"076"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"121"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"070"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"043"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"181"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"159"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"120"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"154"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"052"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"010"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"110"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"042"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"114"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"078"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"156"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"061"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"107"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"172"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"182"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"193"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"168"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"104"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"065"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"112"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"088"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"035"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"188"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"186"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"046"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"132"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"097"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"102"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"129"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"049"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"028"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"001"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"139"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"025"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"178"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"017"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"050"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"004"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"103"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"012"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"041"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"138"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"024"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"174"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"192"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"128"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"027"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"059"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"131"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"119"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"057"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"106"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"173"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"069"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"152"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"136"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"044"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"141"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"066"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"170"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"086"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"039"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"032"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"077"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"064"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"126"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"056"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"071"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"006"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    TEST_ASSERT_EQUAL_STRING("091", btree_search(btree, (void *)"091"));
    TEST_ASSERT_EQUAL_STRING("022", btree_search(btree, (void *)"022"));
    TEST_ASSERT_EQUAL_STRING("097", btree_search(btree, (void *)"097"));
    TEST_ASSERT_EQUAL_STRING("065", btree_search(btree, (void *)"065"));
    TEST_ASSERT_EQUAL_STRING("154", btree_search(btree, (void *)"154"));
    TEST_ASSERT_EQUAL_STRING("193", btree_search(btree, (void *)"193"));
    TEST_ASSERT_EQUAL_STRING("112", btree_search(btree, (void *)"112"));
    TEST_ASSERT_EQUAL_STRING("136", btree_search(btree, (void *)"136"));
    TEST_ASSERT_EQUAL_STRING("172", btree_search(btree, (void *)"172"));
    TEST_ASSERT_EQUAL_STRING("069", btree_search(btree, (void *)"069"));
    TEST_ASSERT_EQUAL_STRING("186", btree_search(btree, (void *)"186"));
    TEST_ASSERT_EQUAL_STRING("032", btree_search(btree, (void *)"032"));
    TEST_ASSERT_EQUAL_STRING("015", btree_search(btree, (void *)"015"));
    TEST_ASSERT_EQUAL_STRING("034", btree_search(btree, (void *)"034"));
    TEST_ASSERT_EQUAL_STRING("164", btree_search(btree, (void *)"164"));
    TEST_ASSERT_EQUAL_STRING("120", btree_search(btree, (void *)"120"));
    TEST_ASSERT_EQUAL_STRING("061", btree_search(btree, (void *)"061"));
    TEST_ASSERT_EQUAL_STRING("075", btree_search(btree, (void *)"075"));
    TEST_ASSERT_EQUAL_STRING("141", btree_search(btree, (void *)"141"));
    TEST_ASSERT_EQUAL_STRING("012", btree_search(btree, (void *)"012"));
    TEST_ASSERT_EQUAL_STRING("121", btree_search(btree, (void *)"121"));
    TEST_ASSERT_EQUAL_STRING("183", btree_search(btree, (void *)"183"));
    TEST_ASSERT_EQUAL_STRING("168", btree_search(btree, (void *)"168"));
    TEST_ASSERT_EQUAL_STRING("104", btree_search(btree, (void *)"104"));
    TEST_ASSERT_EQUAL_STRING("028", btree_search(btree, (void *)"028"));
    TEST_ASSERT_EQUAL_STRING("052", btree_search(btree, (void *)"052"));
    TEST_ASSERT_EQUAL_STRING("071", btree_search(btree, (void *)"071"));
    TEST_ASSERT_EQUAL_STRING("056", btree_search(btree, (void *)"056"));
    TEST_ASSERT_EQUAL_STRING("057", btree_search(btree, (void *)"057"));
    TEST_ASSERT_EQUAL_STRING("110", btree_search(btree, (void *)"110"));
    TEST_ASSERT_EQUAL_STRING("010", btree_search(btree, (void *)"010"));
    TEST_ASSERT_EQUAL_STRING("103", btree_search(btree, (void *)"103"));
    TEST_ASSERT_EQUAL_STRING("042", btree_search(btree, (void *)"042"));
    TEST_ASSERT_EQUAL_STRING("013", btree_search(btree, (void *)"013"));
    TEST_ASSERT_EQUAL_STRING("025", btree_search(btree, (void *)"025"));
    TEST_ASSERT_EQUAL_STRING("026", btree_search(btree, (void *)"026"));
    TEST_ASSERT_EQUAL_STRING("114", btree_search(btree, (void *)"114"));
    TEST_ASSERT_EQUAL_STRING("177", btree_search(btree, (void *)"177"));
    TEST_ASSERT_EQUAL_STRING("001", btree_search(btree, (void *)"001"));
    TEST_ASSERT_EQUAL_STRING("007", btree_search(btree, (void *)"007"));
    TEST_ASSERT_EQUAL_STRING("066", btree_search(btree, (void *)"066"));
    TEST_ASSERT_EQUAL_STRING("119", btree_search(btree, (void *)"119"));
    TEST_ASSERT_EQUAL_STRING("039", btree_search(btree, (void *)"039"));
    TEST_ASSERT_EQUAL_STRING("049", btree_search(btree, (void *)"049"));
    TEST_ASSERT_EQUAL_STRING("152", btree_search(btree, (void *)"152"));
    TEST_ASSERT_EQUAL_STRING("064", btree_search(btree, (void *)"064"));
    TEST_ASSERT_EQUAL_STRING("024", btree_search(btree, (void *)"024"));
    TEST_ASSERT_EQUAL_STRING("030", btree_search(btree, (void *)"030"));
    TEST_ASSERT_EQUAL_STRING("059", btree_search(btree, (void *)"059"));
    TEST_ASSERT_EQUAL_STRING("128", btree_search(btree, (void *)"128"));
    TEST_ASSERT_EQUAL_STRING("134", btree_search(btree, (void *)"134"));
    TEST_ASSERT_EQUAL_STRING("181", btree_search(btree, (void *)"181"));
    TEST_ASSERT_EQUAL_STRING("050", btree_search(btree, (void *)"050"));
    TEST_ASSERT_EQUAL_STRING("170", btree_search(btree, (void *)"170"));
    TEST_ASSERT_EQUAL_STRING("008", btree_search(btree, (void *)"008"));
    TEST_ASSERT_EQUAL_STRING("166", btree_search(btree, (void *)"166"));
    TEST_ASSERT_EQUAL_STRING("129", btree_search(btree, (void *)"129"));
    TEST_ASSERT_EQUAL_STRING("080", btree_search(btree, (void *)"080"));
    TEST_ASSERT_EQUAL_STRING("070", btree_search(btree, (void *)"070"));
    TEST_ASSERT_EQUAL_STRING("138", btree_search(btree, (void *)"138"));
    TEST_ASSERT_EQUAL_STRING("106", btree_search(btree, (void *)"106"));
    TEST_ASSERT_EQUAL_STRING("035", btree_search(btree, (void *)"035"));
    TEST_ASSERT_EQUAL_STRING("131", btree_search(btree, (void *)"131"));
    TEST_ASSERT_EQUAL_STRING("027", btree_search(btree, (void *)"027"));
    TEST_ASSERT_EQUAL_STRING("017", btree_search(btree, (void *)"017"));
    TEST_ASSERT_EQUAL_STRING("178", btree_search(btree, (void *)"178"));
    TEST_ASSERT_EQUAL_STRING("192", btree_search(btree, (void *)"192"));
    TEST_ASSERT_EQUAL_STRING("182", btree_search(btree, (void *)"182"));
    TEST_ASSERT_EQUAL_STRING("063", btree_search(btree, (void *)"063"));
    TEST_ASSERT_EQUAL_STRING("077", btree_search(btree, (void *)"077"));
    TEST_ASSERT_EQUAL_STRING("130", btree_search(btree, (void *)"130"));
    TEST_ASSERT_EQUAL_STRING("173", btree_search(btree, (void *)"173"));
    TEST_ASSERT_EQUAL_STRING("088", btree_search(btree, (void *)"088"));
    TEST_ASSERT_EQUAL_STRING("086", btree_search(btree, (void *)"086"));
    TEST_ASSERT_EQUAL_STRING("076", btree_search(btree, (void *)"076"));
    TEST_ASSERT_EQUAL_STRING("004", btree_search(btree, (void *)"004"));
    TEST_ASSERT_EQUAL_STRING("102", btree_search(btree, (void *)"102"));
    TEST_ASSERT_EQUAL_STRING("156", btree_search(btree, (void *)"156"));
    TEST_ASSERT_EQUAL_STRING("092", btree_search(btree, (void *)"092"));
    TEST_ASSERT_EQUAL_STRING("041", btree_search(btree, (void *)"041"));
    TEST_ASSERT_EQUAL_STRING("044", btree_search(btree, (void *)"044"));
    TEST_ASSERT_EQUAL_STRING("047", btree_search(btree, (void *)"047"));
    TEST_ASSERT_EQUAL_STRING("038", btree_search(btree, (void *)"038"));
    TEST_ASSERT_EQUAL_STRING("153", btree_search(btree, (void *)"153"));
    TEST_ASSERT_EQUAL_STRING("019", btree_search(btree, (void *)"019"));
    TEST_ASSERT_EQUAL_STRING("085", btree_search(btree, (void *)"085"));
    TEST_ASSERT_EQUAL_STRING("126", btree_search(btree, (void *)"126"));
    TEST_ASSERT_EQUAL_STRING("187", btree_search(btree, (void *)"187"));
    TEST_ASSERT_EQUAL_STRING("159", btree_search(btree, (void *)"159"));
    TEST_ASSERT_EQUAL_STRING("078", btree_search(btree, (void *)"078"));
    TEST_ASSERT_EQUAL_STRING("107", btree_search(btree, (void *)"107"));
    TEST_ASSERT_EQUAL_STRING("132", btree_search(btree, (void *)"132"));
    TEST_ASSERT_EQUAL_STRING("174", btree_search(btree, (void *)"174"));
    TEST_ASSERT_EQUAL_STRING("122", btree_search(btree, (void *)"122"));
    TEST_ASSERT_EQUAL_STRING("139", btree_search(btree, (void *)"139"));
    TEST_ASSERT_EQUAL_STRING("043", btree_search(btree, (void *)"043"));
    TEST_ASSERT_EQUAL_STRING("046", btree_search(btree, (void *)"046"));
    TEST_ASSERT_EQUAL_STRING("196", btree_search(btree, (void *)"196"));
    TEST_ASSERT_EQUAL_STRING("006", btree_search(btree, (void *)"006"));
    TEST_ASSERT_EQUAL_STRING("188", btree_search(btree, (void *)"188"));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Insert an item into a B-tree, check that it is not NULL, and then de-initialize it
 */
static void test_insert_same_key(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));

    char *act_str_04 = (char *)btree_search(btree, (void *)"04");
    TEST_ASSERT_EQUAL(act_str_04, exp_str_04);
    TEST_ASSERT_EQUAL_STRING(act_str_04, exp_str_04);

    char exp_str2_04[] = {'0', '4', '\0'};
    TEST_ASSERT_NOT_EQUAL(exp_str_04, exp_str2_04);
    TEST_ASSERT_EQUAL_STRING(exp_str_04, exp_str2_04);

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str2_04));
    char *act_str2_04 = (char *)btree_search(btree, (void *)"04");
    TEST_ASSERT_EQUAL(act_str2_04, exp_str2_04);
    TEST_ASSERT_EQUAL_STRING(act_str_04, exp_str2_04);
    TEST_ASSERT_NOT_EQUAL(act_str_04, act_str2_04);

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 1
 *
 * @note case 1, the key to delete is in the root node, and the root is a leaf
 *
 * before:
 * 0[01, 02, 03, 04, 05]
 *
 * After
 * 0[01, 02, 03, 05]
 */
static void test_delete_case1(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));

    btree_delete(btree, (void *)"04");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"04"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 2a
 *
 * Before
 * 0[06]
 * 1[01, 02, 03, 04, 05] 1[07, 08]
 *
 * After
 * 0[05]
 * 1[01, 02, 03, 04] 1[07, 08]
 */
static void test_delete_case2a(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"06");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"06"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 2b
 *
 * Before
 * 0[03]
 * 1[01, 02] 1[04, 05, 06, 07, 08]
 *
 * After
 * 0[04]
 * 1[01, 02] 1[05, 06, 07, 08]
 */
static void test_delete_case2b(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // Now delete the item in the root, but with a right node that has < t node
    btree_delete(btree, (void *)"03");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"03"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 2c
 *
 * @note case 2b, the key to delete is in the root node, this would leave the root will < t items
 *       The root node has children, and both left child and right child have < t items
 *       merge the children and then move an item up before deleting the item in root
 *
 *       In this case the irem is the last in the root so the hight of the three is reduced.
 */
static void test_delete_case2c_empty_root(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // Delete the items in the left and right children first to set up the case
    btree_delete(btree, (void *)"04");
    btree_delete(btree, (void *)"05");
    TEST_ASSERT_TRUE(btree_validate(btree));

    // Now delete the item in the root, but with  left and right  node that has < t node
    btree_delete(btree, (void *)"03");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"03"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 3al
 *
 */
static void test_delete_case3al(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // Now delete the item in the root, but with  left and right  node that has < t node
    btree_delete(btree, (void *)"05");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"05"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 3ar
 *
 * befor:
 *           0[03,         06]
 * 1[01, 02]     1[04, 05]    1[07, 08, 09]
 *
 *           0[03,          07]
 * 1[01, 02]      1[04, 06]     1[08, 09]
 */
static void test_delete_case3ar(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"05");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"05"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 2c
 *
 * @note case 2b, the key to delete is in the root node, this would leave the root will < t items
 *       The root node has children, and both left child and right child have < t items
 *       merge the children and then move an item up before deleting the item in root
 *
 *       In this case the root node has more than one item
 *
 * Before
 * 0[03, 07]
 * 1[01, 02] 1[04, 06] 1[08, 09]
 *
 * After
 * 0[03]
 * 1[01, 02] 1[04, 06, 08, 09]
 */
static void test_delete_case2c(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // Delete the items in the left and right children first to set up the case
    // This ends up testing case 3ar as an unfortunate sideeffect
    btree_delete(btree, (void *)"05");

    // Now delete the item in the root, but with  left and right  node that has < t node
    btree_delete(btree, (void *)"07");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"07"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a tree with a hight on 2
 *
 * Before
 * 0[03, 06, 09, 12, 15]
 * 1[01, 02] 1[04, 05] 1[07, 08] 1[10, 11] 1[13, 14] 1[16, 17, 18]
 *
 * After
 * 0[]
 */
static void test_delete_two_hight(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";
    char *exp_str_13 = "13";
    char *exp_str_14 = "14";
    char *exp_str_15 = "15";
    char *exp_str_16 = "16";
    char *exp_str_17 = "17";
    char *exp_str_18 = "18";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_13));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_14));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_15));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_16));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_17));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_18));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"18");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"17");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"16");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"15");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"14");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"13");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"12");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"11");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"10");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"09");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"08");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"07");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"06");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"05");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"04");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"03");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"02");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"01");
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 3a
 *
 * @note case 3al, the key to delete is in the child node,
 *
 * Before:
 *                             0[ 09 ]
 *        1[03,         06]                    1[12,            15]
 * 2[01, 02]   2[04, 05]    2[07, 08]   2[10, 11]     2[13, 14]     2[16, 17, 18, 19, 20]
 *
 * After:
 *        0[03,                 09,         12,          15]
 * 1[01, 02]   1[04, 05, 06, 08]   1[10, 11]    1[13, 14]   1[16, 17, 18]
 */
static void test_delete_case3b(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";
    char *exp_str_13 = "13";
    char *exp_str_14 = "14";
    char *exp_str_15 = "15";
    char *exp_str_16 = "16";
    char *exp_str_17 = "17";
    char *exp_str_18 = "18";
    char *exp_str_19 = "19";
    char *exp_str_20 = "20";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_13));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_14));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_15));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_16));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_17));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_18));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_19));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_20));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"07");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"07"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 2a this children
 *
 * Before:
 * Delete=>13                                0[13,                             22]
 *            1[04,      07,        10]        ~        1[16,       19]        ~        1[25,       28]        ~
 * 2[01, 02, 03] 2[05, 06] 2[08, 09] 2[11, 12] ~ 2[14, 15] 2[17, 18] 2[20, 21] ~ 2[23, 24] 2[26, 27] 2[29, 30] ~
 *
 * After fist delete:
 *                                   0[12,                22]
 *            1[04,       07,       10]    ~        1[16,      19]        ~         1[25,       28]        ~
 * 2[01, 02, 03] 2[05, 06] 2[08, 09] 2[11] ~ 2[14, 15] 2[17, 18] 2[20, 21] ~ 2[23, 24] 2[26, 27] 2[29, 30] ~
 *
 * After second delete:
 *                                 0[10,                                    22]
 *            1[04,      07]         ~                1[16,      19]         ~        1[25,      28]         ~
 * 2[01, 02, 03] 2[05, 06] 2[08, 09] ~ 2[11, 12, 14, 15] 2[17, 18] 2[20, 21] ~ 2[23, 24] 2[26, 27] 2[29, 30] ~
 *
 */
static void test_delete_case2a_with_children(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";
    char *exp_str_13 = "13";
    char *exp_str_14 = "14";
    char *exp_str_15 = "15";
    char *exp_str_16 = "16";
    char *exp_str_17 = "17";
    char *exp_str_18 = "18";
    char *exp_str_19 = "19";
    char *exp_str_20 = "20";
    char *exp_str_21 = "21";
    char *exp_str_22 = "22";
    char *exp_str_23 = "23";
    char *exp_str_24 = "24";
    char *exp_str_25 = "25";
    char *exp_str_26 = "26";
    char *exp_str_27 = "27";
    char *exp_str_28 = "28";
    char *exp_str_29 = "29";
    char *exp_str_30 = "30";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_30));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_29));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_28));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_27));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_26));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_25));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_24));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_23));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_22));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_21));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_20));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_19));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_18));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_17));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_16));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_15));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_14));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_13));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"13");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"13"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"13");
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 2b this children
 *
 *
 * Before:
 * Delete=>18                          0[09,                               18]
 *        1[03,       06]        ~        1[12,       15]        ~        1[21,      24,       27]             ~
 * 2[01, 02] 2[04, 05] 2[07, 08] ~ 2[10, 11] 2[13, 14] 2[16, 17] ~ 2[19, 20] 2[22, 23] 2[25, 26] 2[28, 29, 30] ~
 *
 * After first delete
 *                              0[09,                           19]
 *        1[03,       06]        ~        1[12,       15]        ~    1[21,      24,       27]             ~
 * 2[01, 02] 2[04, 05] 2[07, 08] ~ 2[10, 11] 2[13, 14] 2[16, 17] ~ 2[20] 2[22, 23] 2[25, 26] 2[28, 29, 30] ~
 *
 * After second delete
 *                             0[09,                                    21]
 *        1[03,       06]        ~        1[12,                   19]    ~        1[24,       27]            ~
 * 2[01, 02] 2[04, 05] 2[07, 08] ~ 2[10, 11] 2[13, 14, 15, 16, 17]  2[20] ~ 2[22, 23] 2[25, 26] 2[28, 29, 30] ~
 *
 */
static void test_delete_case2b_with_children(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";
    char *exp_str_13 = "13";
    char *exp_str_14 = "14";
    char *exp_str_15 = "15";
    char *exp_str_16 = "16";
    char *exp_str_17 = "17";
    char *exp_str_18 = "18";
    char *exp_str_19 = "19";
    char *exp_str_20 = "20";
    char *exp_str_21 = "21";
    char *exp_str_22 = "22";
    char *exp_str_23 = "23";
    char *exp_str_24 = "24";
    char *exp_str_25 = "25";
    char *exp_str_26 = "26";
    char *exp_str_27 = "27";
    char *exp_str_28 = "28";
    char *exp_str_29 = "29";
    char *exp_str_30 = "30";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_13));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_14));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_15));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_16));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_17));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_18));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_19));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_20));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_21));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_22));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_23));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_24));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_25));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_26));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_27));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_28));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_29));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_30));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"18");
    TEST_ASSERT_TRUE(btree_validate(btree));
    TEST_ASSERT_NULL(btree_search(btree, (void *)"18"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"18");
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 3al
 */
static void test_delete_case3al_with_children(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";
    char *exp_str_13 = "13";
    char *exp_str_14 = "14";
    char *exp_str_15 = "15";
    char *exp_str_16 = "16";
    char *exp_str_17 = "17";
    char *exp_str_18 = "18";
    char *exp_str_19 = "19";
    char *exp_str_20 = "20";
    char *exp_str_21 = "21";
    char *exp_str_22 = "22";
    char *exp_str_23 = "23";
    char *exp_str_24 = "24";
    char *exp_str_25 = "25";
    char *exp_str_26 = "26";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_26));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_25));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_24));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_23));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_22));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_21));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_20));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_19));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_18));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_17));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_16));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_15));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_14));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_13));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"21");
    TEST_ASSERT_TRUE(btree_validate(btree));

    TEST_ASSERT_NULL(btree_search(btree, (void *)"21"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"21");
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Delete a key using case 3ar
 *
 */
static void test_delete_case3ar_with_children(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    char *exp_str_01 = "01";
    char *exp_str_02 = "02";
    char *exp_str_03 = "03";
    char *exp_str_04 = "04";
    char *exp_str_05 = "05";
    char *exp_str_06 = "06";
    char *exp_str_07 = "07";
    char *exp_str_08 = "08";
    char *exp_str_09 = "09";
    char *exp_str_10 = "10";
    char *exp_str_11 = "11";
    char *exp_str_12 = "12";
    char *exp_str_13 = "13";
    char *exp_str_14 = "14";
    char *exp_str_15 = "15";
    char *exp_str_16 = "16";
    char *exp_str_17 = "17";
    char *exp_str_18 = "18";
    char *exp_str_19 = "19";
    char *exp_str_20 = "20";
    char *exp_str_21 = "21";
    char *exp_str_22 = "22";
    char *exp_str_23 = "23";
    char *exp_str_24 = "24";
    char *exp_str_25 = "25";
    char *exp_str_26 = "26";

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_01));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_02));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_03));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_04));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_05));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_06));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_07));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_08));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_09));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_10));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_11));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_12));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_13));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_14));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_15));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_16));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_17));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_18));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_19));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_20));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_21));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_22));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_23));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_24));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_25));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)exp_str_26));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"06");

    TEST_ASSERT_NULL(btree_search(btree, (void *)"06"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"06");
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

/**
 * @brief Insert an item into a B-tree, check that it is not NULL, and then de-initialize it
 *
 * 0[030,                                                        066,                                                                             110,                                                           152]
 * 1[008, 017, 025]                                            1[039, 046, 050, 059]                                                            1[080, 088, 107]                                               1[129, 134]                                    1[166, 177, 188]
 * 2[001, 004, 006, 007] 2[010, 013] 2[019, 024] 2[026, 027]   2[035, 038] 2[041, 042, 043, 044] 2[047, 049] 2[056, 057] 2[063, 064, 070, 071]  2[076, 077, 078] 2[085, 086] 2[092, 102, 103, 106] 2[114, 119] 2[130, 131, 132] 2[130, 131, 132] 2[138, 139]  2[153, 156, 159] 2[170, 173, 174] 2[178, 181, 182, 187] 2[192, 196]
 *
 */
static void test_delete_random_order(void)
{
    btree_t *btree = btree_init(3, sizeof(char *), &mock_item_compare);

    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"019"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"091"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"080"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"187"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"134"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"130"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"092"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"085"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"183"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"177"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"075"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"034"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"030"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"007"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"122"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"164"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"008"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"196"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"015"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"063"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"038"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"013"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"047"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"026"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"153"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"166"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"022"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"076"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"121"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"070"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"043"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"181"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"159"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"120"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"154"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"052"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"010"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"110"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"042"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"114"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"078"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"156"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"061"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"107"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"172"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"182"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"193"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"168"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"104"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"065"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"112"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"088"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"035"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"188"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"186"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"046"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"132"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"097"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"102"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"129"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"049"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"028"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"001"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"139"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"025"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"178"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"017"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"050"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"004"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"103"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"012"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"041"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"138"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"024"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"174"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"192"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"128"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"027"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"059"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"131"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"119"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"057"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"106"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"173"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"069"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"152"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"136"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"044"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"141"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"066"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"170"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"086"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"039"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"032"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"077"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"064"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"126"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"056"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"071"));
    TEST_ASSERT_EQUAL(EXIT_SUCCESS, btree_insert(btree, (void *)"006"));
    TEST_ASSERT_TRUE(btree_validate(btree));

    btree_delete(btree, (void *)"091");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"022");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"097");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"065");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"154");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"193");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"112");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"136");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"172");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"069");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"186");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"032");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"015");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"034");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"164");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"120");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"061");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"075");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"141");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"012");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"121");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"183");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"168");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"104");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"028");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"052");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"071");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"056");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"057");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"110");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"010");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"103");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"042");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"013");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"025");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"026");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"114");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"177");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"001");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"007");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"066");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"119");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"039");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"049");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"152");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"064");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"024");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"030");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"059");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"128");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"134");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"181");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"050");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"170");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"008");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"166");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"129");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"080");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"070");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"138");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"106");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"035");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"131");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"027");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"017");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"178");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"192");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"182");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"063");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"077");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"130");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"173");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"088");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"086");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"076");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"004");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"102");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"156");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"092");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"041");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"044");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"047");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"038");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"153");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"019");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"085");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"126");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"187");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"159");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"078");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"107");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"132");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"174");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"122");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"139");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"043");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"046");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"196");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"006");
    TEST_ASSERT_TRUE(btree_validate(btree));
    btree_delete(btree, (void *)"188");
    TEST_ASSERT_TRUE(btree_validate(btree));

    // De-initialize the B-tree
    btree_deinit(&btree);
}

int btree_test_main(const char *test_name)
{
    UNITY_BEGIN();
    if (strcmp(test_name, "test_init") == 0)
    {
        RUN_TEST(test_init);
    }
    else if (strcmp(test_name, "test_insert") == 0)
    {
        RUN_TEST(test_insert);
    }
    else if (strcmp(test_name, "test_fill_root_node") == 0)
    {
        RUN_TEST(test_fill_root_node);
    }
    else if (strcmp(test_name, "test_simple_tree") == 0)
    {
        RUN_TEST(test_simple_tree);
    }
    else if (strcmp(test_name, "test_insert_random") == 0)
    {
        RUN_TEST(test_insert_random);
    }
    else if (strcmp(test_name, "test_search") == 0)
    {
        RUN_TEST(test_search);
    }
    else if (strcmp(test_name, "test_search_random_order") == 0)
    {
        RUN_TEST(test_search_random_order);
    }
    else if (strcmp(test_name, "test_insert_same_key") == 0)
    {
        RUN_TEST(test_insert_same_key);
    }
    else if (strcmp(test_name, "test_delete_case1") == 0)
    {
        RUN_TEST(test_delete_case1);
    }
    else if (strcmp(test_name, "test_delete_case2a") == 0)
    {
        RUN_TEST(test_delete_case2a);
    }
    else if (strcmp(test_name, "test_delete_case2b") == 0)
    {
        RUN_TEST(test_delete_case2b);
    }
    else if (strcmp(test_name, "test_delete_case3al") == 0)
    {
        RUN_TEST(test_delete_case3al);
    }
    else if (strcmp(test_name, "test_delete_case3ar") == 0)
    {
        RUN_TEST(test_delete_case3ar);
    }
    else if (strcmp(test_name, "test_delete_case2c") == 0)
    {
        RUN_TEST(test_delete_case2c);
    }
    else if (strcmp(test_name, "test_delete_case2c_empty_root") == 0)
    {
        RUN_TEST(test_delete_case2c_empty_root);
    }
    else if (strcmp(test_name, "test_delete_two_hight") == 0)
    {
        RUN_TEST(test_delete_two_hight);
    }
    else if (strcmp(test_name, "test_delete_case3b") == 0)
    {
        RUN_TEST(test_delete_case3b);
    }
    else if (strcmp(test_name, "test_delete_case2a_with_children") == 0)
    {
        RUN_TEST(test_delete_case2a_with_children);
    }
    else if (strcmp(test_name, "test_delete_case2b_with_children") == 0)
    {
        RUN_TEST(test_delete_case2b_with_children);
    }
    else if (strcmp(test_name, "test_delete_case3al_with_children") == 0)
    {
        RUN_TEST(test_delete_case3al_with_children);
    }
    else if (strcmp(test_name, "test_delete_case3ar_with_children") == 0)
    {
        RUN_TEST(test_delete_case3ar_with_children);
    }
    else if (strcmp(test_name, "test_delete_random_order") == 0)
    {
        RUN_TEST(test_delete_random_order);
    }
    return UNITY_END();
}