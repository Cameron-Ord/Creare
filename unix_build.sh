working_dir=$(pwd)
build_dir=build

cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE \
  -S. \
  -B./build \
  -G "Unix Makefiles"

cd build
make -j$(nproc)
