add_library(Include INTERFACE)
target_link_libraries(Include INTERFACE CompilerFlags)
target_include_directories(Include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
