enable_testing()

add_executable(CppScratchPadTests 
    LinkedListTests.cpp DoublyLinkedListTests.cpp StdContainerTests.cpp
    SortArrayAlgosTests.cpp HeapTests.cpp BSTTests.cpp
    AVLTests.cpp SpanTests.cpp HashMapTests.cpp StringAlgosTests.cpp
    BigMathTests.cpp GraphTests.cpp AlgoPracticeTests.cpp
)

# Use system GTest if found, otherwise use FetchContent's gtest_main
if(GTest_FOUND)
    # Re-import the GTest targets in this scope
    find_package(GTest CONFIG REQUIRED)
    find_package(Threads REQUIRED)
    target_link_libraries(CppScratchPadTests GTest::gtest GTest::gtest_main Threads::Threads)
else()
    target_link_libraries(CppScratchPadTests gtest_main)
endif()
target_link_libraries(CppScratchPadTests MainLib)

include(GoogleTest)

target_compile_definitions(CppScratchPadTests PRIVATE LARGE_N=10000)

gtest_discover_tests(CppScratchPadTests)
