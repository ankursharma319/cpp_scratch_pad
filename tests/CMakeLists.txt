enable_testing()

add_executable(CppScratchPadTests LinkedListTests.cpp)

target_link_libraries(CppScratchPadTests gtest_main)
target_link_libraries(CppScratchPadTests MainLib)

include(GoogleTest)

gtest_discover_tests(CppScratchPadTests)
