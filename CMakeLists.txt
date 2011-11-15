cmake_minimum_required(VERSION 2.6)

project(libfi)

enable_testing()

# Setup output paths.
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all libraries.")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin CACHE PATH
    "Single output directory for building all executables.")
mark_as_advanced(LIBRARY_OUTPUT_PATH EXECUTABLE_OUTPUT_PATH)

add_subdirectory(src)
add_subdirectory(tools)
add_subdirectory(tests)