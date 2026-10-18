#!/usr/bin/env bash
noctalia msg notification-show "build.sh" "building..." >/dev/null

cmake -G Ninja -B build \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DSFML_BUILD_NETWORK=OFF -DSFML_BUILD_AUDIO=OFF .
cmake --build build/
if [[ -e "build/bin/resources" ]]; then
  ln -sr resources build/bin/resources
fi
if [[ -e app_loclink ]]; then
  exit
fi
ln -s build/bin/application app_loclink
