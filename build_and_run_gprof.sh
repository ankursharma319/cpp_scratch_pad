#! /bin/bash

cmake --build _build/gprof_ready/ \
&& ./_build/gprof_ready/src-exe/MainExe \
&& gprof --graph --flat-profile ./_build/gprof_ready/src-exe/MainExe gmon.out > gprof.out \
&& gprof ./_build/gprof_ready/src-exe/MainExe | gprof2dot |  dot -Tsvg -o gprof_output.svg
