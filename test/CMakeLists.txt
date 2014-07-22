cmake_minimum_required (VERSION 2.6)
project (Test_suite_for_NUt)

include_directories ("${PROJECT_SOURCE_DIR}/../include")
include_directories ("$ENV{CATCH_DIR}/include")

add_executable(Errors errors.cpp)
add_executable(Helpers helpers.cpp)
add_executable(Log log.cpp)
add_executable(Timings timings.cpp)
add_executable(Progress progress.cpp)
