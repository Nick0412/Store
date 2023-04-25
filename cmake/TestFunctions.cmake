include_guard(GLOBAL)

# Helper function to create a test which will link against Gtest libraries.
function(add_complex_test)
    set(options "")
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES LIBRARIES)
    cmake_parse_arguments(CUSTOM_TEST "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN})

    if(NOT DEFINED CUSTOM_TEST_NAME)
        message(FATAL_ERROR "NAME is required for a complex test.")
    endif()

    string(CONCAT TEST_TARGET "${CUSTOM_TEST_NAME}" "Target")
    list(APPEND GTEST_LIBS GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

    add_executable("${TEST_TARGET}" "${CUSTOM_TEST_SOURCES}")
    target_link_libraries("${TEST_TARGET}" "${GTEST_LIBS}" "${CUSTOM_TEST_LIBRARIES}")
    target_include_directories("${TEST_TARGET}" PRIVATE "include")
    add_test(NAME "${CUSTOM_TEST_NAME}" COMMAND "${TEST_TARGET}")

    return()
endfunction()
