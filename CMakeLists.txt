cmake_minimum_required(VERSION 3.20)
project(Store)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(GTest REQUIRED)

### Libraries ###
add_library(Common STATIC "src/common/StringUtils.cpp")
target_include_directories(Common PRIVATE "include")

add_library(Networking STATIC "src/networking/Common.cpp")
target_include_directories(Networking PRIVATE "include")


### Tests ###
enable_testing()

add_executable(StringUtilsTest "test/common/StringUtilsTest.cpp")
target_link_libraries(StringUtilsTest Common 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock 
    GTest::gmock_main)
target_include_directories(StringUtilsTest PRIVATE "include")
add_test(NAME StringUtils COMMAND StringUtilsTest)

add_executable(NetworkingCommonTest "test/networking/CommonTest.cpp")
target_link_libraries(NetworkingCommonTest Networking 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock 
    GTest::gmock_main
    Common)
target_include_directories(NetworkingCommonTest PRIVATE "include")
add_test(NAME NetworkingCommon COMMAND NetworkingCommonTest)
