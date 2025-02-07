add_library(Sort INTERFACE)
target_link_libraries(Sort INTERFACE CompilerFlags)
target_include_directories(Sort INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${ALGORITHMS_ROOT_DIR})
