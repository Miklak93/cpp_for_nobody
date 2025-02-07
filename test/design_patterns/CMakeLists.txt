# Include required packages
include(CTest)
include(GoogleTest)

#include test functions
include(${PROJECT_CMAKE_DIR}/Test.cmake)

# Add tests with sources and libraries
add_google_test(CreationalTest
    SOURCES creational_test.cpp
    LIBRARIES Creational)

add_google_test(StructuralTest
    SOURCES structural_test.cpp
    LIBRARIES Structural)

add_google_test(BehavioralTest
    SOURCES behavioral_test.cpp
    LIBRARIES Behavioral)
