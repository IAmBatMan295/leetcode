# ── Minimum CMake version required to use this file ──────────────────────────
# 3.16 is old enough to work almost everywhere, new enough for modern features.
cmake_minimum_required(VERSION 3.16)

# ╔════════════════════════════════════════════════════════════════════════════╗
# ║  TEMPLATE — Copy this file into your project root and rename it to       ║
# ║  CMakeLists.txt. Then customize the sections marked with CHANGE/ADD.     ║
# ║                                                                          ║
# ║  Rules:                                                                  ║
# ║    - All your .c / .cpp / .h / .hpp files go inside a folder called src/ ║
# ║    - Anything outside src/ is ignored by the build (notes, docs, etc.)   ║
# ║    - Headers (.h/.hpp) are NOT compiled. They get included by .c/.cpp    ║
# ║      files via #include. The compiler copy-pastes the header contents    ║
# ║      into the .cpp before compiling. So headers are always compiled      ║
# ║      as PART OF the .cpp that includes them — never on their own.        ║
# ║                                                                          ║
# ║  Build with the shell helpers (defined in your .zshrc):                  ║
# ║    cmakebuild -m   → MERGED mode (all .c/.cpp → one executable)         ║
# ║    cmakebuild -i   → INDIVIDUAL mode (each .c/.cpp → its own exe)       ║
# ║    cmbuild         → rebuild without reconfiguring                       ║
# ║    cmrun <name>    → run ./build/<name>                                  ║
# ║    cmclean         → delete build/ and compile_commands.json             ║
# ╚════════════════════════════════════════════════════════════════════════════╝

# ── Project name (CHANGE THIS per project) ───────────────────────────────────
# "C CXX" means this project can contain both C and C++ code.
# If you only use C++, you can remove "C". If only C, remove "CXX".
project(MyProject C CXX)

# ── Language standards ───────────────────────────────────────────────────────
# These tell the compiler which version of C/C++ to use.
# C17 = latest stable C standard.  C++20 = modern C++ with concepts, ranges, etc.
# REQUIRED = fail if the compiler doesn't support it (instead of silently downgrading).
# EXTENSIONS OFF = use strict standard C++, no compiler-specific extras (more portable).
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ── Compile-commands for clangd ──────────────────────────────────────────────
# This makes CMake generate a file called compile_commands.json inside build/.
# clangd (your LSP in neovim/vscode) reads this file to understand how each
# file is compiled — what flags, what include paths, etc. Without it, clangd
# can't give you accurate errors/completions.
# Your shell function cmakebuild then symlinks it to the project root so
# clangd can find it (clangd looks for it in the project root by default).
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ══════════════════════════════════════════════════════════════════════════════
# STEP 1: FIND EXTERNAL LIBRARIES (ADD YOUR find_package CALLS HERE)
# ══════════════════════════════════════════════════════════════════════════════
# find_package() searches your system for an installed library.
# If found, it creates "imported targets" (like Qt6::Widgets) that you can
# link against later in Step 3.
#
# ── Example: Qt6 ─────────────────────────────────────────────────────────────
# Qt needs these three lines BEFORE find_package. They tell CMake to
# automatically handle Qt's special code generation:
#   AUTOMOC = auto-generate meta-object code for QObject classes
#   AUTOUIC = auto-compile .ui designer files
#   AUTORCC = auto-compile .qrc resource files
#
#   set(CMAKE_AUTOMOC ON)
#   set(CMAKE_AUTOUIC ON)
#   set(CMAKE_AUTORCC ON)
#
#   find_package(Qt6 COMPONENTS Widgets REQUIRED)
#
# Qt6 on GCC adds a flag (-mno-direct-extern-access) that confuses clangd.
# These lines strip it out so clangd doesn't show false warnings:
#
#   get_target_property(_opts Qt6::Core INTERFACE_COMPILE_OPTIONS)
#   if(_opts)
#       list(REMOVE_ITEM _opts "-mno-direct-extern-access")
#       set_target_properties(Qt6::Core PROPERTIES INTERFACE_COMPILE_OPTIONS "${_opts}")
#   endif()
#   string(REPLACE "-mno-direct-extern-access" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
#   string(REPLACE "-mno-direct-extern-access" "" CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}")
#
# ── Example: ncurses ─────────────────────────────────────────────────────────
#   find_package(Curses REQUIRED)
#
# ── Example: SDL2 ────────────────────────────────────────────────────────────
#   find_package(SDL2 REQUIRED)
#
# ── Example: POSIX threads ───────────────────────────────────────────────────
#   find_package(Threads REQUIRED)
#
# ── Example: pkg-config based libraries ──────────────────────────────────────
#   find_package(PkgConfig REQUIRED)
#   pkg_check_modules(NCURSES REQUIRED ncurses)

# ══════════════════════════════════════════════════════════════════════════════
# STEP 2: BUILD MODE — controls how executables are created
# ══════════════════════════════════════════════════════════════════════════════
# MERGED    = combine ALL .c/.cpp files into one executable called "main".
#             Use this when your files work together (e.g. main.cpp calls
#             functions from utils.cpp which includes utils.hpp).
#
# INDIVIDUAL = each .c/.cpp becomes its own separate executable.
#              Use this when each file is a standalone program (e.g. homework
#              problems, small experiments). The executable name = filename
#              without extension (hello.cpp → ./build/hello).
#
# Default is MERGED. You pick the mode via cmakebuild -m or cmakebuild -i.
set(BUILD_MODE "MERGED" CACHE STRING "INDIVIDUAL = one exe per .c/.cpp | MERGED = single exe")
set_property(CACHE BUILD_MODE PROPERTY STRINGS INDIVIDUAL MERGED)

# ── Collect source files from src/ ───────────────────────────────────────────
# GLOB_RECURSE = search src/ and all its subdirectories.
# CONFIGURE_DEPENDS = re-scan when you add/remove files (so you don't have to
#                     re-run cmake manually every time you add a new .cpp).
# We ONLY collect .c and .cpp here because those are what the compiler builds.
# Headers (.h/.hpp) don't go here — they're pulled in automatically by
# #include directives inside your .c/.cpp files.
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

# ── Common settings ──────────────────────────────────────────────────────────
# Put compiled executables directly in build/ (not build/src/ or some subfolder).
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Compiler warnings — catch bugs early. These work on GCC and Clang:
#   -Wall      = enable most warnings
#   -Wextra    = enable even more warnings
#   -Wpedantic = warn about non-standard code
set(COMMON_WARN_FLAGS -Wall -Wextra -Wpedantic)

# ══════════════════════════════════════════════════════════════════════════════
# STEP 3: BUILD TARGETS — this is where executables are created and linked
# ══════════════════════════════════════════════════════════════════════════════

# ── INDIVIDUAL mode ──────────────────────────────────────────────────────────
if(BUILD_MODE STREQUAL "INDIVIDUAL")
    message(STATUS "Build mode: INDIVIDUAL — one executable per source file")

    # Loop through every .c/.cpp file and make a separate executable from each.
    foreach(SRC IN LISTS ALL_SOURCES)
        # Extract just the filename without path or extension.
        # e.g. /home/user/project/src/hello.cpp → hello
        get_filename_component(TARGET_NAME "${SRC}" NAME_WE)

        # Create an executable named after the source file.
        # Only the .c/.cpp file is listed here — NOT headers.
        add_executable(${TARGET_NAME} "${SRC}")

        # Apply warning flags to this target.
        # PRIVATE = only applies to this target, not to anything that depends on it.
        target_compile_options(${TARGET_NAME} PRIVATE ${COMMON_WARN_FLAGS})

        # Tell the compiler where to look when it sees #include "something.hpp".
        # This makes #include work for any header inside src/.
        target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")

        # ── Link external libraries to this target (ADD YOURS HERE) ──────
        # target_link_libraries connects your code to an external library so
        # you can use its functions. Without it you get "undefined reference" errors.
        #
        # ── Example: Qt6 ──
        #   target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Widgets)
        #
        # ── Example: ncurses ──
        #   target_link_libraries(${TARGET_NAME} PRIVATE ${CURSES_LIBRARIES})
        #   target_include_directories(${TARGET_NAME} PRIVATE ${CURSES_INCLUDE_DIRS})
        #
        # ── Example: SDL2 ──
        #   target_link_libraries(${TARGET_NAME} PRIVATE SDL2::SDL2)
        #
        # ── Example: POSIX threads ──
        #   target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads)

        message(STATUS "  -> ${TARGET_NAME}")
    endforeach()

# ── MERGED mode ──────────────────────────────────────────────────────────────
elseif(BUILD_MODE STREQUAL "MERGED")
    message(STATUS "Build mode: MERGED — single executable from all sources")

    # Combine ALL .c/.cpp files into one executable called "main".
    # The compiler will compile each .c/.cpp separately, then the linker
    # joins them all together. Headers are found via #include automatically.
    add_executable(main ${ALL_SOURCES})

    target_compile_options(main PRIVATE ${COMMON_WARN_FLAGS})

    # Let any file do #include "anything_in_src.hpp" without a relative path.
    target_include_directories(main PRIVATE "${CMAKE_SOURCE_DIR}/src")

    # ── Link external libraries to merged target (ADD YOURS HERE) ────────
    # Same as above, but using "main" as the target name instead of ${TARGET_NAME}.
    #
    # ── Example: Qt6 ──
    #   target_link_libraries(main PRIVATE Qt6::Widgets)
    #
    # ── Example: ncurses ──
    #   target_link_libraries(main PRIVATE ${CURSES_LIBRARIES})
    #   target_include_directories(main PRIVATE ${CURSES_INCLUDE_DIRS})
    #
    # ── Example: SDL2 ──
    #   target_link_libraries(main PRIVATE SDL2::SDL2)
    #
    # ── Example: POSIX threads ──
    #   target_link_libraries(main PRIVATE Threads::Threads)

else()
    message(FATAL_ERROR "Unknown BUILD_MODE '${BUILD_MODE}'. Use INDIVIDUAL or MERGED.")
endif()
