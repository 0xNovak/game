
cmake -G Ninja -B build \
  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
  -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DSFML_BUILD_NETWORK=OFF -DSFML_BUILD_AUDIO=OFF .
cmake --build build/
if [[ -e "build/bin/resources" ]]; then
  ln -sr resources build/bin/resources
fi
ln -s build/bin/application app_local_
