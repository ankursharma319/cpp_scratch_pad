#! /bin/bash

cmake --build _build/gprof_ready/ \
&& ./_build/gprof_ready/tests/CppScratchPadTests \
&& gprof --graph --flat-profile ./_build/gprof_ready/tests/CppScratchPadTests gmon.out > gprof.out \
&& gprof ./_build/gprof_ready/tests/CppScratchPadTests | gprof2dot |  dot -Tsvg -o gprof_output.svg
