#!/bin/bash

do_log() {
	echo "[Neat]" "${@}"
}

readonly build_configuration=${1:-Debug}
readonly build_target=${2:-all}

do_log "Build configuration: ${build_configuration}."
do_log "Build target: ${build_target}."

curr_dir_full="$(pwd)"
curr_dir="$(basename "${curr_dir_full}")"

if [[ "${curr_dir}" == "Scripts" ]]; then
	root_dir="$(realpath "..")"
else
	root_dir="$(realpath ".")"
fi

build_dir="${root_dir}/build"

do_log "Current working dir: ${curr_dir_full}."
do_log "Build dir: ${build_dir}."

do_log "Initializing submodules."
git submodule update --init --recursive

do_log "Removing build cache."
rm -f "${build_dir}/CMakeCache.txt"

do_log "Configuring build."
cmake -S "${root_dir}" -B "${build_dir}" -DCMAKE_BUILD_TYPE="${build_configuration}"

do_log "Building target '${build_target}'."
cmake --build "${build_dir}" --config "${build_configuration}" --target "${build_target}" -j 6 --

