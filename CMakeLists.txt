cmake_minimum_required(VERSION 3.10.0)
project(flash_store VERSION 0.1.0 LANGUAGES C)

add_library(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC
    # use the directory of this CMakeLists.txt as include path
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_sources(${PROJECT_NAME}  PRIVATE
    src/btree.c
    src/store.c
)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE -O2 /W4 /WX)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O2 -Wall -Wextra -Wcast-align  -Wconversion  -Wstrict-prototypes -Wpedantic -Werror -Wsuggest-attribute=const )
# -Wall -Wextra -Werror -Wconversion -pedantic
    # -Werror GCC option must be used. In addition the following GCC options should be used to prevent questionable coding practice:
    # -Werror, -Wall, -Wcast-align, -Wstrict-prototypes

endif()


include(CTest)
enable_testing()

add_subdirectory(tests)