#! /bin/sh

# run ./configure.sh first

cmake --build _build/debug/ \
&& gdb \
-ex 'break Board::fromFen' \
-ex 'info b' \
-ex 'set print pretty on' \
-ex 'run' \
./_build/debug/src-exe/MainExe
