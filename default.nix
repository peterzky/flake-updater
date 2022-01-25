{ stdenv, meson, ninja, pkg-config, json_c }:
stdenv.mkDerivation rec {
  pname = "flake-updater";
  version = "0.0.1";

  src = ./.;

  nativeBuildInputs = [
    meson
    ninja
    pkg-config
    json_c
  ];

}
