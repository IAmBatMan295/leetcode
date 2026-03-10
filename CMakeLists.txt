cmake_minimum_required(VERSION 3.16)

project(MyProject C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(BUILD_MODE "MERGED" CACHE STRING "INDIVIDUAL = one exe per .c/.cpp | MERGED = single exe")
set_property(CACHE BUILD_MODE PROPERTY STRINGS INDIVIDUAL MERGED)

if(NOT EXISTS "${CMAKE_SOURCE_DIR}/src")
    message(FATAL_ERROR "'src/' directory not found in project root.")
endif()

file(GLOB_RECURSE ALL_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/src/*.c"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

if(NOT ALL_SOURCES)
    message(FATAL_ERROR "No .c / .cpp files found under src/.")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(COMMON_WARN_FLAGS -Wall -Wextra -Wpedantic)

if(BUILD_MODE STREQUAL "INDIVIDUAL")
    message(STATUS "Build mode: INDIVIDUAL — one executable per source file")

    foreach(SRC IN LISTS ALL_SOURCES)

        get_filename_component(TARGET_NAME "${SRC}" NAME_WE)

        add_executable(${TARGET_NAME} "${SRC}")

        target_compile_options(${TARGET_NAME} PRIVATE ${COMMON_WARN_FLAGS})

        target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")

        message(STATUS "  -> ${TARGET_NAME}")
    endforeach()

elseif(BUILD_MODE STREQUAL "MERGED")
    message(STATUS "Build mode: MERGED — single executable from all sources")

    add_executable(main ${ALL_SOURCES})

    target_compile_options(main PRIVATE ${COMMON_WARN_FLAGS})

    target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/src")

else()
    message(FATAL_ERROR "Unknown BUILD_MODE '${BUILD_MODE}'. Use INDIVIDUAL or MERGED.")
endif()
