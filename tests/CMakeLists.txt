find_package(GTest CONFIG REQUIRED)

add_executable(run_tests test_math.cpp)

target_link_libraries(run_tests
    PRIVATE
        GTest::gtest
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(run_tests)
