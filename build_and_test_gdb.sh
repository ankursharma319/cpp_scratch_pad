#! /bin/sh

# run ./configure.sh first
#-ex 'break ankur::linked_list::sort' \

cmake --build _build/debug/ \
&& gdb \
-ex 'break linked_list.hpp:428' \
-ex 'info b' \
-ex 'set print pretty on' \
-ex 'run' \
./_build/debug/tests/CppScratchPadTests
