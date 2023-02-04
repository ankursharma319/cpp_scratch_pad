{ pkgs ? import (fetchTarball "https://github.com/NixOS/nixpkgs/archive/95642fb287d3ea743d0401770f0b2043646d0032.tar.gz") {}}:

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
        pkgs.clang_15
    ];
}
