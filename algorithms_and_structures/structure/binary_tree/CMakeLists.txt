add_library(BinaryTree INTERFACE)
target_link_libraries(BinaryTree INTERFACE CompilerFlags)
target_include_directories(BinaryTree INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${ALGORITHMS_ROOT_DIR})