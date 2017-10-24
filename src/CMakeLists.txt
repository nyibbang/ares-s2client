# Setup MSVC parallelized builds
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

include_directories(
  "../contrib/s2client-api/include"
  "${PROJECT_BINARY_DIR}/contrib/s2client-api/generated"
)

set(ARES_S2CLIENT_HEADERS
  "bot.hpp"
  "functional.hpp"
  "geometry.hpp"
)

set(ARES_S2CLIENT_SOURCES
  "bot.cpp"
  "main.cpp"
  "geometry.cpp"
)

add_executable(ares-s2client
  ${ARES_S2CLIENT_HEADERS}
  ${ARES_S2CLIENT_SOURCES}
)
target_link_libraries(ares-s2client sc2api sc2utils)
target_include_directories(ares-s2client PUBLIC ${Boost_INCLUDE_DIR})
