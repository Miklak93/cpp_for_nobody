function(add_google_test target)
    # Collect all arguments except the first (target name)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs SOURCES LIBRARIES VARIABLES)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Create the executable with the specified sources
    add_executable(${target} ${ARG_SOURCES})

    # Link libraries
    target_link_libraries(${target} PUBLIC gtest_main gmock_main ${ARG_LIBRARIES})

    # Define a compile-time variable using target_compile_definitions
    target_compile_definitions(${target} PRIVATE ${ARG_VARIABLES})

    # Set include directories
    target_include_directories(${target} PRIVATE ${PROJECT_ROOT_DIR})

    # Disable strict flags for the target
    disable_strict_flags(${target})

    # Discover Google Test cases
    gtest_discover_tests(${target})
endfunction()