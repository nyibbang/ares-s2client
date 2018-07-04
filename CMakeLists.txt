cmake_minimum_required(VERSION 3.1)

project(ares-s2client)

# Use bin as the directory for all executables.
# This will make protoc easy to find.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Windows builds subdirectories Debug/Release.
# These variables will overwrite that and put binaries in bin.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_BINARY_DIR}/bin)

# Build with c++17 support.
set(CMAKE_CXX_STANDARD 17)

# Allow creating filters for projects in visual studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Development tools files
configure_file("${PROJECT_SOURCE_DIR}/.clang.in" "${PROJECT_SOURCE_DIR}/.clang")
configure_file("${PROJECT_SOURCE_DIR}/.lvimrc.in" "${PROJECT_SOURCE_DIR}/.lvimrc")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE CACHE BOOLEAN "Export compile commands" FORCE)
add_definitions(-DARES_ROOT="${PROJECT_SOURCE_DIR}")

###############################################################################
# options
###############################################################################
option(ARES_DEBUG "Enables ares debugging tools." FALSE)

###############################################################################
# Boost
###############################################################################
if (NOT DEFINED Boost_USE_STATIC_LIBS)
  set(Boost_USE_STATIC_LIBS OFF CACHE BOOLEAN "" FORCE)
endif()

if (NOT DEFINED Boost_USE_MULTITHREADED)
  set(Boost_USE_MULTITHREADED ON CACHE BOOLEAN "" FORCE)
endif()
find_package(Boost 1.65.0 REQUIRED)

###############################################################################
# contrib
###############################################################################
add_subdirectory("contrib/s2client-api")

###############################################################################
# sources
###############################################################################
add_subdirectory("src")
