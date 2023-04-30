#! /bin/sh

# https://web.stanford.edu/class/archive/cs/cs107/cs107.1174/guide_callgrind.html

if [ "$(expr substr $(uname -s) 1 5)" != "Linux" ]; then
    echo "valgrind only available on linux";
    exit 1;
fi

cmake --build _build/debug/ \
&& valgrind \
--tool=callgrind \
--simulate-cache=yes \
--callgrind-out-file=callgrind.out \
./_build/debug/tests/CppScratchPadTests

# --gtest_filter=*HashMapTest.test_larger_input

gprof2dot -f callgrind callgrind.out | dot -Tsvg -o callgrind_output.svg
