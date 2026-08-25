cmake_minimum_required(VERSION 3.16)
project(harware_calc)


add_executable(hardware_calc main.cpp)

target_include_directories(hardware_calc PRIVATE include)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.9.0
)
FetchContent_MakeAvailable(yaml-cpp)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

target_link_libraries(hardware_calc PRIVATE yaml-cpp::yaml-cpp)

enable_testing()

add_executable(hardware_calc_tests
        tests/test_calculator.cpp
)

target_link_libraries(hardware_calc_tests
        PRIVATE GTest::gtest_main
)

target_include_directories(hardware_calc_tests PRIVATE include)

include(GoogleTest)
gtest_discover_tests(hardware_calc_tests)