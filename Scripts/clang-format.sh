#!/bin/bash
set -x

declare -r -a dirs=("Sandbox" "Neat/src" "Tests" "Examples" "NeatEditor")

for dir in "${dirs[@]}"; do
	find "${dir}" -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.hpp" -o -name "*.c" -o -name "*.inl" \) -exec clang-format -i {} +
done
