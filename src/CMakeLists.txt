# Setup MSVC parallelized builds
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

###############################################################################
# executable
###############################################################################
set(config_file_output "${CMAKE_CURRENT_BINARY_DIR}/generated/config.hpp")
configure_file(
  "config.hpp.in"
  ${config_file_output}
)

set(ARES_S2CLIENT_HEADERS
  "agent.hpp"
  "functional.hpp"
  "geometry.hpp"
  "utility.hpp"
  "decision.hpp"
  ${config_file_output}
)

set(ARES_S2CLIENT_SOURCES
  "agent.cpp"
  "geometry.cpp"
  "decision.cpp"
)

if (ARES_DEBUG)
  list(APPEND ARES_S2CLIENT_HEADERS "debug.hpp")
  list(APPEND ARES_S2CLIENT_SOURCES "debug.cpp")
endif()

add_library(
  ares_s2client
    ${ARES_S2CLIENT_HEADERS}
    ${ARES_S2CLIENT_SOURCES}
)

target_include_directories(
  ares_s2client
    INTERFACE
      "${CMAKE_CURRENT_SOURCE_DIR}"
    PUBLIC
      # boost
      "${Boost_INCLUDE_DIR}"
      # sc2api
      "${PROJECT_SOURCE_DIR}/contrib/s2client-api/include"
      "${PROJECT_BINARY_DIR}/contrib/s2client-api/generated"
      # generated
      "${CMAKE_CURRENT_BINARY_DIR}/generated"
)

target_link_libraries(
  ares_s2client
    sc2api
    sc2utils
)

###############################################################################
# executable
###############################################################################
add_executable(ares_s2client_bot
  "main.cpp"
)

target_link_libraries(
  ares_s2client_bot
    ares_s2client
)
