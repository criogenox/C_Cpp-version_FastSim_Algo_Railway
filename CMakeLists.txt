cmake_minimum_required(VERSION 3.28)
set(PROJECT_NAME "FastSim")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
set(default_build_type "Release")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -std=c++20")
set(TARGET ${PROJECT_NAME})
set(TARGET_SRC ${PROJECT_NAME}_src)
set(TARGET_TEST "${PROJECT_NAME}Test")
set(TARGET_LIB "${PROJECT_NAME}_lib")
#-----------#-----------#-----------#

include(FetchContent) # (3) Gtest with linked library
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.14.0)
FetchContent_MakeAvailable(googletest)
#-----------#-----------#-----------#

set(LIBS_PATH "${PROJECT_SOURCE_DIR}/libs") # (2) standalone with library linking
set(HEADERS_PATH "${PROJECT_SOURCE_DIR}/headers")
set(SRC_PATH "${PROJECT_SOURCE_DIR}/src")
set(TEST_PATH "${PROJECT_SOURCE_DIR}/test") # (3) Gtest with linked library
#-----------#-----------#-----------#

include_directories(${HEADERS_PATH})
link_directories(${LIBS_PATH}) # (2) standalone with library linking

file(GLOB_RECURSE CPPS "${SRC_PATH}/*.cpp")
file(GLOB_RECURSE CPPT "${TEST_PATH}/*.cpp") # (3) Gtest with linked library
#-----------#-----------#-----------#

add_executable(${TARGET_SRC} ${CPPS}) # (0) compile with complete source code
#-----------#-----------#-----------#

add_library(${TARGET_LIB} STATIC ${SRC_PATH}/fastsim.cpp) # (1) library compilation
add_executable(${TARGET} ${SRC_PATH}/main.cpp) # (1) test with linked library
#                                                (2) standalone with library linking
target_link_libraries(${TARGET} fastsim_lib)   # (1) test with linked library
#                                                (2) standalone with library linking
#-----------#-----------#-----------#

add_executable(${TARGET_TEST} ${CPPT}) # (3) Gtest with linked library
target_link_libraries(${TARGET_TEST} ${TARGET_LIB} gtest_main gmock_main)
#-----------#-----------#-----------#