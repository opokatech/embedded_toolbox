include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.1.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(et_tests
    DigitalInputTests.cpp
    CircularBufferTests.cpp
    MovingAverageTests.cpp
)

target_link_libraries(et_tests PRIVATE embedded_toolbox Catch2::Catch2WithMain)

enable_testing()
add_test(all_tests et_tests)
