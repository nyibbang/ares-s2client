enable_testing()

set(ARES_S2CLIENT_TESTS_HEADERS)

set(ARES_S2CLIENT_TESTS_SOURCES
  "test_functional.cpp"
)

add_executable(
  ares_s2client_tests
    ${ARES_S2CLIENT_TESTS_HEADERS}
    ${ARES_S2CLIENT_TESTS_SOURCES}
)

target_link_libraries(
  ares_s2client_tests
    ares_s2client
    gmock_main
)

add_test(
  NAME ares_s2client_tests
  COMMAND ares_s2client_tests
)
