{
  description = "Cpp scratchpad flake";
  nixConfig.bash-prompt-suffix = "\[nix\] ";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      # System types to support.
      supportedSystems = [ "x86_64-linux" "x86_64-darwin" "aarch64-linux" "aarch64-darwin" ];

      # Helper function to generate an attrset '{ x86_64-linux = f "x86_64-linux"; ... }'.
      forAllSystems = nixpkgs.lib.genAttrs supportedSystems;

      # Nixpkgs instantiated for supported system types.
      nixpkgsFor = forAllSystems (system: import nixpkgs { inherit system; });
    in
    {
      # Utilized by `nix develop`
      devShell = forAllSystems (system:
        let
          pkgs = nixpkgsFor.${system};
        in
        pkgs.mkShell {
          nativeBuildInputs = [
              pkgs.cmake
          ];
          buildInputs = if pkgs.stdenv.isDarwin then [] else [pkgs.valgrind] ++ [
              pkgs.gtest
              pkgs.git
              pkgs.gdb
              pkgs.which
              pkgs.gprof2dot
              pkgs.xdot
              pkgs.graphviz
              pkgs.clang_22
          ];
        }

      );
      # utilized by `nix build .`
      defaultPackage = forAllSystems(system:
        let
          pkgs = nixpkgsFor.${system};
        in
        pkgs.stdenv.mkDerivation {
          pname = "cpp-scratch-pad";
          version = "0.1.0";
          src = ./.;

          nativeBuildInputs = [ pkgs.cmake ];
          buildInputs = [ pkgs.gtest ];

          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Debug"
          ];

          doCheck = true;
          checkPhase = ''
            ./tests/CppScratchPadTests
          '';

          installPhase = ''
            mkdir -p $out/bin
            cp src-exe/MainExe $out/bin/
            cp tests/CppScratchPadTests $out/bin/
          '';

          meta.mainProgram = "CppScratchPadTests";
        }
      );

      # utilized by `nix build .#callgrind` and `nix run .#callgrind`
      packages = forAllSystems(system:
        let
          pkgs = nixpkgsFor.${system};
          mainPackage = self.defaultPackage.${system};
        in
        {
          default = mainPackage;
          callgrind = pkgs.writeShellScriptBin "run-callgrind" ''
            set -e
            OUTPUT_DIR="''${1:-.}"
            echo "Running tests under callgrind..."
            ${pkgs.valgrind}/bin/valgrind \
              --tool=callgrind \
              --simulate-cache=yes \
              --callgrind-out-file="$OUTPUT_DIR/callgrind.out" \
              ${mainPackage}/bin/CppScratchPadTests
            echo "Generating callgrind visualization..."
            ${pkgs.gprof2dot}/bin/gprof2dot -f callgrind "$OUTPUT_DIR/callgrind.out" | \
              ${pkgs.graphviz}/bin/dot -Tsvg -o "$OUTPUT_DIR/callgrind_output.svg"
            echo "Output written to $OUTPUT_DIR/callgrind_output.svg"
          '';
        }
      );

      # Apps for `nix run`
      apps = forAllSystems(system:
        let
          pkgs = nixpkgsFor.${system};
        in
        {
          default = {
            type = "app";
            program = "${self.defaultPackage.${system}}/bin/CppScratchPadTests";
          };
          callgrind = {
            type = "app";
            program = "${self.packages.${system}.callgrind}/bin/run-callgrind";
          };
        }
      );
    };
}
