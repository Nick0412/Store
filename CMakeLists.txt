cmake_minimum_required(VERSION 3.20)
project(Store)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/12a5852e451baabc79c63a86c634912c563d57bc.zip
)

include(TestFunctions)


# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# TODO: Set output paths to separate static libs, dynamic libs, and executables.

# TODO: Consider breaking this up into multiple CMAKE files for readability
# or define macros to glob files into targets more easily/nicely

### Libraries ###
add_library(Common STATIC
    "src/common/StringUtils.cpp"
    "src/common/Platform.cpp"
    "src/common/ThreadPool.cpp")
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
    "src/messages/MessageHelper.cpp"
    "src/messages/GetMessageRequest.cpp"
    "src/messages/GetMessageResponse.cpp"
    "src/messages/PutMessageRequest.cpp"
    "include/messages/MessageBase.h"
    "include/messages/GetMessageRequest.h"
    "include/messages/PutMessageRequest.h"
    "include/messages/GetMessageResponse.h"
    "include/messages/MessageHelper.h"
    "include/messages/MessageType.h")
target_include_directories(Messages PRIVATE "include")
target_link_libraries(Messages Common)


###################################################################################################
#                                           TESTS SECTION 
###################################################################################################
# TODO: Look into `gtest_add_tests` for automatic test pickup
enable_testing()

add_complex_test(
    NAME        "StringUtilsTest"
    SOURCES     "test/common/StringUtilsTest.cpp"
                "test/common/ThreadPoolTest.cpp"
    LIBRARIES   "Common")

add_complex_test(
    NAME        "NetworkingTest"
    SOURCES     "test/networking/CommonTest.cpp"
                "test/networking/EndpointTest.cpp"
    LIBRARIES   "Networking"
                "Common")

add_complex_test(
    NAME        "MessagesTest"
    SOURCES     "test/messages/MessageHelperTest.cpp"
                "test/messages/GetMessageRequestTest.cpp"
                "test/messages/GetMessageResponseTest.cpp"
                "test/messages/PutMessageRequestTest.cpp"
    LIBRARIES   "Messages")