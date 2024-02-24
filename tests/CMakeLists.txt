cmake_minimum_required(VERSION 3.26)

project(Test_CarLudGine)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(Test_CarLudGine
    test.cpp
)

target_link_libraries(Test_CarLudGine
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(Test_CarLudGine)