cmake_minimum_required(VERSION 3.10.0)
project(test_main VERSION 0.1.0 LANGUAGES C)

set(TARGET_SOURCES
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/btree.c>
    src/test_main.c
    src/test_btree.c
    src/test_store.c
    # Unit test framework source file
    Unity/unity.c
)

add_executable(${PROJECT_NAME}
    ${TARGET_SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE
    # use the directory of this CMakeLists.txt as include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    # use  the sub directory of Unity
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Unity>
    # use the directory of main CMakeLists.txt /include
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wcast-align -Wstrict-prototypes -Wpedantic -Werror -Wsuggest-attribute=const )
    # target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wsuggest-attribute=const)
        # -Wsuggest-attribute=format -Wformat=2 -Wshadow -Wconversion -Wsign-conversion
        # -Wnull-dereference -Wdouble-promotion -Wfloat-equal -Wformat-nonliteral
        # -Wformat-security -Wformat=2)

    # -Werror GCC option must be used. In addition the following GCC options should be used to prevent questionable coding practice:
    # -Werror, -Wall, -Wcast-align, -Wstrict-prototypes

endif()

# Define the tests
include(CTest)
add_test(NAME test_btree_init                           COMMAND $<TARGET_FILE:test_main> btree test_init)
add_test(NAME test_btree_insert                         COMMAND $<TARGET_FILE:test_main> btree test_insert)
add_test(NAME test_btree_fill_root_node                 COMMAND $<TARGET_FILE:test_main> btree test_fill_root_node)
add_test(NAME test_btree_simple_tree                    COMMAND $<TARGET_FILE:test_main> btree test_simple_tree)
add_test(NAME test_btree_insert_random                  COMMAND $<TARGET_FILE:test_main> btree test_insert_random)
add_test(NAME test_btree_search                         COMMAND $<TARGET_FILE:test_main> btree test_search)
add_test(NAME test_btree_search_random_order            COMMAND $<TARGET_FILE:test_main> btree test_search_random_order)
add_test(NAME test_btree_insert_same_key                COMMAND $<TARGET_FILE:test_main> btree test_insert_same_key)
add_test(NAME test_btree_delete_case1                   COMMAND $<TARGET_FILE:test_main> btree test_delete_case1)
add_test(NAME test_btree_delete_case2a                  COMMAND $<TARGET_FILE:test_main> btree test_delete_case2a)
add_test(NAME test_btree_delete_case2b                  COMMAND $<TARGET_FILE:test_main> btree test_delete_case2b)
add_test(NAME test_btree_delete_case3al                 COMMAND $<TARGET_FILE:test_main> btree test_delete_case3al)
add_test(NAME test_btree_delete_case3ar                 COMMAND $<TARGET_FILE:test_main> btree test_delete_case3ar)
add_test(NAME test_btree_delete_case2c                  COMMAND $<TARGET_FILE:test_main> btree test_delete_case2c)
add_test(NAME test_btree_delete_case2c_empty_root       COMMAND $<TARGET_FILE:test_main> btree test_delete_case2c_empty_root)
add_test(NAME test_btree_delete_two_hight               COMMAND $<TARGET_FILE:test_main> btree test_delete_two_hight)
add_test(NAME test_btree_delete_case3b                  COMMAND $<TARGET_FILE:test_main> btree test_delete_case3b)
add_test(NAME test_btree_delete_case2a_with_children    COMMAND $<TARGET_FILE:test_main> btree test_delete_case2a_with_children)
add_test(NAME test_btree_delete_case2b_with_children    COMMAND $<TARGET_FILE:test_main> btree test_delete_case2b_with_children)
add_test(NAME test_btree_delete_case3al_with_children   COMMAND $<TARGET_FILE:test_main> btree test_delete_case3al_with_children)
add_test(NAME test_btree_delete_case3ar_with_children   COMMAND $<TARGET_FILE:test_main> btree test_delete_case3ar_with_children)
add_test(NAME test_btree_delete_random_order            COMMAND $<TARGET_FILE:test_main> btree test_delete_random_order)

add_test(NAME test_store_init                           COMMAND $<TARGET_FILE:test_main> store test_init)
