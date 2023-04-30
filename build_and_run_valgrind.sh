#! /bin/sh

if [ "$(expr substr $(uname -s) 1 5)" != "Linux" ]; then
    echo "valgrind only available on linux";
    exit 1;
fi

cmake --build _build/debug/ \
&& valgrind \
--leak-check=full \
--show-leak-kinds=all \
--track-origins=yes \
--log-file=valgrind-out.txt \
./_build/debug/src-exe/MainExe
