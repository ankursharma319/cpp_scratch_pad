#! /bin/sh

cmake --build _build/debug/ \
&& catchsegv ./_build/debug/tests/CppScratchPadTests

#--gtest_filter=StringAlgosPerformanceTest*
