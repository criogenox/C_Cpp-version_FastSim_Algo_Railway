cmake_minimum_required(VERSION 3.28)
project(FastSim VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# Default to Release build
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif ()

# ================== BUILD OPTIONS (switch) ==================
option(BUILD_STATIC_LIB "Build the static library FastSim" ON)
option(BUILD_MAIN_EXEC "Build the main executable" ON)
option(BUILD_TESTS "Build GoogleTest suite" ON)

# Paths
set(LIBS_PATH "${PROJECT_SOURCE_DIR}/libs")
set(HEADERS_PATH "${PROJECT_SOURCE_DIR}/headers")
set(SRC_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test")

include_directories(${HEADERS_PATH})

# ====================== STATIC LIBRARY ======================
if (BUILD_STATIC_LIB)
    add_library(FastSim_lib STATIC ${SRC_PATH}/fastsim.cpp)

    set_target_properties(FastSim_lib PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${LIBS_PATH}
            OUTPUT_NAME "fastsim"
            EXPORT_NAME FastSim
    )

    # Install library
    install(TARGETS FastSim_lib
            EXPORT FastSimTargets
            ARCHIVE DESTINATION ${LIBS_PATH}
    )
endif ()

# ==================== MAIN EXECUTABLE =====================
if (BUILD_MAIN_EXEC)
    add_executable(FastSim ${SRC_PATH}/main.cpp)
    if (BUILD_STATIC_LIB)
        target_link_libraries(FastSim PRIVATE FastSim_lib)
    endif ()
endif ()

# ====================== GOOGLE TESTS ======================
if (BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest
            GIT_TAG v1.14.0)

    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)

    file(GLOB_RECURSE TEST_SOURCES "${TEST_PATH}/*.cpp")
    add_executable(FastSimTest ${TEST_SOURCES})

    target_link_libraries(FastSimTest PRIVATE FastSim_lib gtest_main)

    include(GoogleTest)
    enable_testing()
    gtest_discover_tests(FastSimTest)
endif ()