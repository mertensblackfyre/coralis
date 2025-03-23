let
  pkgs = import <nixpkgs> {};
in
  pkgs.mkShell {
    packages = [
    pkgs.gdb
    pkgs.gtest
    pkgs.cmake
    pkgs.pkg-config
    pkgs.meson
    pkgs.ninja
];
  }
