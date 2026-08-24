cmake_minimum_required(VERSION 3.16)
project(homework)


add_executable(homework main.cpp
        )
target_include_directories(homework PRIVATE include)

include(FetchContent)
FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.9.0
)
FetchContent_MakeAvailable(yaml-cpp)

target_link_libraries(homework PRIVATE yaml-cpp::yaml-cpp)
target_compile_definitions(homework PRIVATE PROJECT_ROOT="${CMAKE_SOURCE_DIR}")