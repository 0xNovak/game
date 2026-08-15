{
  description = "game dev flake";
  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };
  outputs = {
    self,
    nixpkgs,
  }: let
    system = "x86_64-linux";
    pkgs = import nixpkgs {inherit system;};

    sheenbidi-src = pkgs.fetchFromGitHub {
      owner = "Tehreer";
      repo = "SheenBidi";
      rev = "v3.0.0";
      hash = "sha256-e/24MlRX+93b34qD2V1+2XVhMh4WEy2qvt9Rgvybwxs=";
    };
  in {
    devShells.${system}.default = pkgs.mkShell.override {stdenv = pkgs.libcxxStdenv;} {
      nativeBuildInputs = with pkgs; [
        cmake
        ninja
        clang-tools
        git
        pkg-config
      ];
      buildInputs = with pkgs; [
        libx11
        libxrandr
        libxcursor
        libxi
        libxext
        libGL
        udev
        freetype
        harfbuzz
        glib
        libsysprof-capture
      ];
      shellHook = ''zsh'';
    };
  };
}
