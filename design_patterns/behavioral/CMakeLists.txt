add_library(Behavioral INTERFACE)
target_link_libraries(Behavioral INTERFACE CompilerFlags)
target_include_directories(Behavioral INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${DESIGN_PATTERNS_ROOT_DIR})
