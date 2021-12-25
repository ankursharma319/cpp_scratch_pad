#! /bin/sh

# run ./configure.sh first

cmake --build _build/release/ \
&& ./_build/release/src-exe/MainExe

#cmake --install _build/ --prefix _install/
#_install/bin/MainExe
