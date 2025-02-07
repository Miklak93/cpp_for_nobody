add_library(Creational INTERFACE)
target_link_libraries(Creational INTERFACE CompilerFlags)
target_include_directories(Creational INTERFACE ${CMAKE_CURRENT_SOURCE_DIR} ${DESIGN_PATTERNS_ROOT_DIR})
