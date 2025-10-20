#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build"
CONFIG="${CMAKE_BUILD_TYPE:-Release}"

while (($#)); do
  case "$1" in
    --build-dir)
      shift
      if (($# == 0)); then
        echo "[abyssforge] error: --build-dir requires a path" >&2
        exit 1
      fi
      BUILD_DIR="$1"
      ;;
    --build-type)
      shift
      if (($# == 0)); then
        echo "[abyssforge] error: --build-type requires a value" >&2
        exit 1
      fi
      CONFIG="$1"
      ;;
    *)
      BUILD_DIR="$1"
      ;;
  esac
  shift || true
done

echo "[abyssforge] Configuring build directory: $BUILD_DIR"
cmake -S "$ROOT_DIR" -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$CONFIG" -DABYSSFORGE_BUILD_TESTS=OFF

echo "[abyssforge] Building targets (configuration: $CONFIG)"
cmake --build "$BUILD_DIR" --config "$CONFIG"

echo "[abyssforge] Build artifacts located in: $BUILD_DIR"
