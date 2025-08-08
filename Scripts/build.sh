#!/bin/bash
readonly build_target=${1:-Debug}
readonly target=${1:-all}

readonly curr_dir="$(basename "$(pwd)")"

if [[ "${curr_dir}" == "build" ]]; then
	build_dir="."
else
	build_dir="./build"
fi

rm "${build_dir}/CMakeCache.txt"
cmake -S. -B "${build_dir}" -DCMAKE_BUILD_TYPE="${build_target}"
cmake --build "${build_dir}" --config "${build_target}" --target "${target}" -j 6 --

