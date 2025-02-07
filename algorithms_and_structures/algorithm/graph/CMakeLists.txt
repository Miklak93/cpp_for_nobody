add_library(Graph INTERFACE)
target_link_libraries(Graph INTERFACE CompilerFlags)
target_include_directories(Graph INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${ALGORITHMS_ROOT_DIR})
