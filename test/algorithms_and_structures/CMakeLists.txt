# Include required packages
include(CTest)
include(GoogleTest)

#include test functions
include(${PROJECT_CMAKE_DIR}/Test.cmake)

# Add tests with sources and libraries
add_google_test(SortingTest
    SOURCES sorting_test.cpp
    LIBRARIES Sort)

add_google_test(BinaryTreeTest
    SOURCES binary_tree_test.cpp
    LIBRARIES BinaryTree)
