#!/bin/bash

readonly scriptdir="$(dirname "$(readlink -f "$0")")"
readonly debug_dir=$scriptdir/build/debug

echo "Building Debug"
cmake -S $scriptdir -B $debug_dir -DCMAKE_BUILD_TYPE=Debug \
    && cmake --build $debug_dir