#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR=${1:-build}
cmake -S . -B "$BUILD_DIR" -DABYSSFORGE_BUILD_TESTS=ON "$@"
cmake --build "$BUILD_DIR"
ctest --test-dir "$BUILD_DIR"
