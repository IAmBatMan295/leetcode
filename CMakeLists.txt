cmake_minimum_required(VERSION 3.16)

project(MyProject C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build mode: INDIVIDUAL or MERGED
set(BUILD_MODE "MERGED" CACHE STRING "Build mode: INDIVIDUAL or MERGED")
set_property(CACHE BUILD_MODE PROPERTY STRINGS INDIVIDUAL MERGED)

# Require src/ to exist
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src")
    message(FATAL_ERROR "Expected a 'src' directory in the project root, but it was not found.")
endif()

# Recursively grab all C and C++ source files under src/
file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

if(SRC_SOURCES STREQUAL "")
    message(FATAL_ERROR "No .c or .cpp files found under src/. Nothing to build.")
endif()

# Put executables directly in build/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(COMMON_WARN_FLAGS
    -Wall
    -Wextra
    -Wpedantic
)

if(BUILD_MODE STREQUAL "INDIVIDUAL")
    message(STATUS "Build mode: INDIVIDUAL (one executable per .c/.cpp)")

    foreach(SRC_FILE IN LISTS SRC_SOURCES)
        get_filename_component(TARGET_NAME "${SRC_FILE}" NAME_WE)

        message(STATUS "Creating executable '${TARGET_NAME}' from ${SRC_FILE}")
        add_executable(${TARGET_NAME} "${SRC_FILE}")

        target_compile_options(${TARGET_NAME} PRIVATE ${COMMON_WARN_FLAGS})
        target_include_directories(${TARGET_NAME} PRIVATE
            "${CMAKE_SOURCE_DIR}/src"
        )
    endforeach()

elseif(BUILD_MODE STREQUAL "MERGED")
    message(STATUS "Build mode: MERGED (single main app from all sources)")

    set(MERGED_TARGET_NAME main)

    add_executable(${MERGED_TARGET_NAME} ${SRC_SOURCES})

    target_compile_options(${MERGED_TARGET_NAME} PRIVATE ${COMMON_WARN_FLAGS})
    target_include_directories(${MERGED_TARGET_NAME} PRIVATE
        "${CMAKE_SOURCE_DIR}/src"
    )

else()
    message(FATAL_ERROR "Unknown BUILD_MODE='${BUILD_MODE}'. Use INDIVIDUAL or MERGED.")
endif()

