enable_testing()

add_executable(CppScratchPadTests 
    LinkedListTests.cpp DoublyLinkedListTests.cpp StdContainerTests.cpp
    SortArrayAlgosTests.cpp HeapTests.cpp BSTTests.cpp
    AVLTests.cpp SpanTests.cpp HashMapTests.cpp
)

target_link_libraries(CppScratchPadTests gtest_main)
target_link_libraries(CppScratchPadTests MainLib)

include(GoogleTest)

target_compile_definitions(CppScratchPadTests PRIVATE LARGE_N=10000)

gtest_discover_tests(CppScratchPadTests)
