# Define functions to enable or disable strict flags
function(enable_strict_flags target)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} INTERFACE
            #-Wall             # Enable all warnings
            #-Wextra           # Enable extra warnings
            #-Wpedantic        # Enforce strict language compliance
            #-Werror           # Treat all warnings as errors
            #-Wshadow          # Warn about shadowed variables
            #-Wunused          # Warn about unused variables/functions
            #-Wconversion      # Warn about type conversions
            #-Wsign-conversion # Warn about signed/unsigned conversions
        )
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} INTERFACE
            /W4              # Enable highest level of warnings
            /WX              # Treat all warnings as errors
        )
    endif()
endfunction()

function(disable_strict_flags target)
    if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE -w) # Disable all warnings
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE /w) # Disable all warnings
    endif()
endfunction()