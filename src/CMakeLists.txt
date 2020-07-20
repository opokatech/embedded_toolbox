# the code to be tested we put in a static library
add_library(sources 
    DigitalInput.cpp
)

# the tests are put here
add_executable(tests 
    MainTests.cpp
    DigitalInputTests.cpp
    CircularBufferTests.cpp
    MovingAverageTests.cpp
)

# ...and they use the code from the library
target_link_libraries(tests PRIVATE sources)
target_include_directories(tests PRIVATE ../externals)

enable_testing()
add_test(all_tests tests)
