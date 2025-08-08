#!/bin/bash
readonly build_target=${1:-Debug}
readonly target=${1:-all}

rm build/CMakeCache.txt
cmake -S. -B ./build -DCMAKE_BUILD_TYPE="${build_target}"
cmake --build ./build --config "${build_target}" --target "${target}" -j 6 --

