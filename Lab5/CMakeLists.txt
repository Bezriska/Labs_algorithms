cmake_minimum_required(VERSION 3.14)
project(Lab5 C CXX)
set(CMAKE_C_STANDARD 11)

add_executable(main src/main.c src/dijkstra.h src/matrix.h)
add_executable(benchmark src/benchmark.c src/dijkstra.h src/matrix.h)
add_executable(tests tests.cpp src/dijkstra.h src/matrix.h)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(tests gtest_main)

enable_testing()
add_test(NAME all_tests COMMAND tests)

add_custom_target(run_main
  COMMAND main
  DEPENDS main
)
add_dependencies(run_main tests)

add_custom_target(run_benchmark
  COMMAND benchmark
  DEPENDS benchmark
)
add_dependencies(run_benchmark run_main)

add_custom_target(run_python
  COMMAND ${CMAKE_COMMAND} -E env python3 ${CMAKE_SOURCE_DIR}/src/make_schedule.py
)
add_dependencies(run_python run_benchmark)

add_custom_target(full_pipeline ALL)
add_dependencies(full_pipeline run_python)
