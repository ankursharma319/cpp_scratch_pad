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
              pkgs.git
              pkgs.gdb
              pkgs.which
              pkgs.python39Packages.gprof2dot
              pkgs.xdot
              pkgs.graphviz
              pkgs.clang_19
          ];
        }

      );
      # utilized by `nix build .`
      defaultPackage = forAllSystems(system:
        let
          pkgs = nixpkgsFor.${system};
        in
        pkgs.hello
      );
    };
}
