
cmake_minimum_required(VERSION 3.10)
project(TimerTest)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(TimerTest test/test.cpp)
target_link_libraries(TimerTest GTest::GTest GTest::Main)
include_directories(${PROJECT_SOURCE_DIR}/inc ${GTEST_INCLUDE_DIRS})

# Google Testの各テストケースごとにCTestのテストを作成する
gtest_add_tests(TARGET TimerTest)

# CTestのテストをひとつだけ作成する
#add_test(NAME AllTests COMMAND TimerTest)

