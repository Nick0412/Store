cmake_minimum_required(VERSION 3.20)
project(Store)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(GTest REQUIRED)

### Libraries ###
add_library(Common STATIC "src/common/StringUtils.cpp")
target_include_directories(Common PRIVATE "include")


### Tests ###
enable_testing()

add_executable(StringUtilsTest "test/common/StringUtilsTest.cpp")
target_link_libraries(StringUtilsTest Common GTest::gtest GTest::gtest_main)
target_include_directories(StringUtilsTest PRIVATE "include")
add_test(NAME StringUtils COMMAND StringUtilsTest)

