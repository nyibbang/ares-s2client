# Setup MSVC parallelized builds
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

include_directories(
  "../contrib/s2client-api/include"
  "${PROJECT_BINARY_DIR}/contrib/s2client-api/generated"
)

add_executable(ares-s2client "main.cpp")
target_link_libraries(ares-s2client sc2api sc2utils)
target_include_directories(ares-s2client PUBLIC ${Boost_INCLUDE_DIR})
