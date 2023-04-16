cmake_minimum_required(VERSION 3.20)
project(Store)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/12a5852e451baabc79c63a86c634912c563d57bc.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# TODO: Consider breaking this up into multiple CMAKE files for readability
# or defien macros to glob files into targets more easily/nicely

### Libraries ###
add_library(Common STATIC "src/common/StringUtils.cpp" "src/common/Platform.cpp")
target_include_directories(Common PRIVATE "include")
if(WIN32)
   target_link_libraries(Common ws2_32)
endif()

add_library(Networking STATIC 
    "src/networking/Common.cpp"
    "src/networking/Endpoint.cpp"
    "src/networking/EndpointBuilder.cpp")
target_include_directories(Networking PRIVATE "include")
target_link_libraries(Networking Common)

add_library(Messages STATIC
    "src/messages/MessageHelper.cpp")
target_include_directories(Messages PRIVATE "include")
target_link_libraries(Messages Common)


### Tests ###
# TODO: Look into `gtest_add_tests` for automatic test pickup
enable_testing()

add_executable(StringUtilsTest "test/common/StringUtilsTest.cpp")
target_link_libraries(StringUtilsTest 
    Common 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock 
    GTest::gmock_main)
target_include_directories(StringUtilsTest PRIVATE "include")
add_test(NAME StringUtils COMMAND StringUtilsTest)

add_executable(NetworkingTest
    "test/networking/CommonTest.cpp"
    "test/networking/EndpointTest.cpp")
target_link_libraries(NetworkingTest 
    Networking 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock 
    GTest::gmock_main
    Common)
target_include_directories(NetworkingTest PRIVATE "include")
add_test(NAME NetworkingCommon COMMAND NetworkingTest)

add_executable(MessagesTest "test/messages/MessageHelperTest.cpp")
target_link_libraries(MessagesTest 
    Messages 
    GTest::gtest 
    GTest::gtest_main 
    GTest::gmock 
    GTest::gmock_main)
target_include_directories(MessagesTest PRIVATE "include")
add_test(NAME MessageTestName COMMAND MessagesTest)