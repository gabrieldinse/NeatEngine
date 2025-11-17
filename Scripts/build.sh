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

scripts_dir="${root_dir}/Scripts"
build_dir="${root_dir}/build"

do_log "Current working dir: ${curr_dir_full}."
do_log "Build dir: ${build_dir}."

do_log "Running clang-format."
${scripts_dir}/clang-format.sh

do_log "Initializing submodules."
git submodule update --init --recursive

mkdir -p "${build_dir}"

#do_log "Removing build cache."
#rm -f "${build_dir}/CMakeCache.txt"

do_log "Configuring build: ${build_configuration}."
cmake -S "${root_dir}" -B "${build_dir}" -DCMAKE_BUILD_TYPE="${build_configuration}"

do_log "Building target: ${build_target}."
if cmake --build "${build_dir}" --verbose --config "${build_configuration}" --target "${build_target}" -j "$(nproc)" -- ; then
    do_log "Build succeeded."
    do_log "Running tests."
    cd "${build_dir}/Tests" && ctest --verbose
else
    do_log "Build failed."
    do_log "Skipping tests."
    exit 1
fi

