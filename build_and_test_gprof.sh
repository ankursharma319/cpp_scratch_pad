#! /bin/bash

if [ "$(expr substr $(uname -s) 1 5)" != "Linux" ]; then
    echo "gprof only available on linux";
    exit 1;
fi

cmake --build _build/gprof_ready/ \
&& ./_build/gprof_ready/tests/CppScratchPadTests \
&& gprof --graph --flat-profile ./_build/gprof_ready/tests/CppScratchPadTests gmon.out > gprof.out \
&& gprof ./_build/gprof_ready/tests/CppScratchPadTests | gprof2dot |  dot -Tsvg -o gprof_output.svg
