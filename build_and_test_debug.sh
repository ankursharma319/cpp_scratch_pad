#! /bin/sh

# run ./configure.sh first

cmake --build _build/debug/ \
&& ./_build/debug/tests/CppScratchPadTests
