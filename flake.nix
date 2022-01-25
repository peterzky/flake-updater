{
  description = "flake updater written in C";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs/master";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      rec {
        packages = {
          flake-updater = pkgs.callPackage ./default.nix { };
        };
        defaultPackage = packages.flake-updater;

        devShell = pkgs.mkShell {
          name = "flake-updater";
          inputsFrom = [ packages.flake-updater ];
          buildInputs = with pkgs; [ clang-tools ];
          shellHook = ''
            update () {
              if [[ -d builddir ]]; then
                rm -rf builddir
              fi
              meson builddir
              ln -sf $PWD/builddir/compile_commands.json .
            }
          '';

        };
      }

    );

}
