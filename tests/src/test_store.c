#include <string.h>
#include "unity.h"

#define DEBUG
#include "store.h"

/**
 * @brief create a store, check that it is not NULL, and then de-initialize it
 */
static void test_init(void)
{
    // create a store with 1 page
    store_t *store = store_init(1);
    TEST_ASSERT_NOT_NULL(store);

    // De-initialize the store
    store_deinit(&store);
    TEST_ASSERT_NULL(store);
}

int store_test_main(const char *test_name)
{
    UNITY_BEGIN();
    if (strcmp(test_name, "test_init") == 0)
    {
        RUN_TEST(test_init);
    }
    return UNITY_END();
}