enable_testing()

add_executable(CppScratchPadTests 
    LinkedListTests.cpp DoublyLinkedListTests.cpp StdContainerTests.cpp
    SortArrayAlgosTests.cpp
)

target_link_libraries(CppScratchPadTests gtest_main)
target_link_libraries(CppScratchPadTests MainLib)

include(GoogleTest)

target_compile_definitions(CppScratchPadTests PRIVATE LARGE_N=1000000)

gtest_discover_tests(CppScratchPadTests)
