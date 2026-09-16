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
        ripgrep
        zsh
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
        sheenbidi-src
      ];
      shellHook = ''
        clang --version | head -n1
        cmake --version | head -n1
        echo "ninja version $(ninja --version)"
        echo ""
        git status | head -n2
        git status | tail -n+4 | sed '2,3d' | head -n +3 | sed 's/.*\(modified:.*\)/\x1b[33m\1\x1b[0m/'
        echo ""
        rg TODO:  | sed 's/^.*TODO:/TODO:/'   | sed 's/.*\(TODO:.*\)/\x1b[34m\1\x1b[0m/'
        rg BUG:   | sed 's/^.*BUG:/BUG:/'     | sed 's/.*\(BUG:.*\)/\x1b[32m\1\x1b[0m/'
        rg FIXME: | sed 's/^.*FIXME:/FIXME:/' | sed 's/.*\(FIXME:.*\)/\x1b[31m\1\x1b[0m/'
        rg HACK:  | sed 's/^.*HACK:/HACK:/'   | sed 's/.*\(HACK:.*\)/\x1b[35m\1\x1b[0m/'
        exec zsh
      '';
    };
  };
}
