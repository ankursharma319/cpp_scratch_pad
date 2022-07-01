{ pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/9a17f325397d137ac4d219ecbd5c7f15154422f4.tar.gz") {}}:

pkgs.mkShell {
    nativeBuildInputs = [
        pkgs.cmake
    ];
    buildInputs = if pkgs.stdenv.isDarwin then [] else [pkgs.valgrind] ++ [
        pkgs.git
        pkgs.gdb
        pkgs.which
        pkgs.python39Packages.gprof2dot
        pkgs.xdot
        pkgs.graphviz
        pkgs.clang_13
    ];
}
