#include <string.h>
#include <stdlib.h> //  EXIT_SUCCESS and EXIT_FAILURE
#include "unity.h"

void setUp(void)
{
    // Set stuff up here
}

void tearDown(void)
{
    // Clean stuff up here
}

// int btree_test_main(const char *test_name);
// int store_test_main(const char *test_name);

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        if (strcmp(argv[1], "btree") == 0)
        {
            // return btree_test_main(argv[2]);
        }
        // else if (strcmp(argv[1], "store") == 0)
        // {
        //     return store_test_main(argv[2]);
        // }
    }
    return EXIT_FAILURE;
}