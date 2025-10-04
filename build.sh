#!/bin/bash

set -ex

rm -rf ./build/* > /dev/null 2>&1
conan install . --build=missing --profile=pilum.txt --output-folder=build
cd build/
source conanbuild.sh
cmake -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd -
