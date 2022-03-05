enable_testing()

add_executable(test_bencode_parser
    bencode_parser_test.cpp
)

target_link_libraries(test_bencode_parser
    bencode_parser
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(test_bencode_parser)
