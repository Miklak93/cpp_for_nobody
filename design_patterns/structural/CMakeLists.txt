add_library(Structural INTERFACE)
target_link_libraries(Structural INTERFACE CompilerFlags)
target_include_directories(Structural INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${DESIGN_PATTERNS_ROOT_DIR})
