#!/bin/bash
readonly build_target=${1:-Debug}
readonly target=${1:-all}

cmake -S. -B ./build
cmake --build ./build --config "${build_target}" --target "${target}" -j 6 --

