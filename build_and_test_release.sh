#! /bin/sh

# run ./configure.sh first

cmake --build _build/release/ \
&& ./_build/release/tests/CppScratchPadTests
