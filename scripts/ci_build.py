#!/usr/bin/env python3
"""Cross-platform CI build helper."""

from __future__ import annotations

import argparse
import os
import platform
import subprocess
from pathlib import Path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build-type", default="Release", choices=["Debug", "Release", "RelWithDebInfo"])
    parser.add_argument("--generator", default=None, help="Optional CMake generator override")
    parser.add_argument("--build-dir", default="build", help="Build directory")
    parser.add_argument("--run-tests", action="store_true", help="Run ctest after building")
    return parser.parse_args()


def run(cmd: list[str], cwd: Path | None = None) -> None:
    print("[ci]", " ".join(cmd))
    subprocess.run(cmd, check=True, cwd=cwd)


def configure(args: argparse.Namespace, build_dir: Path) -> None:
    cmake_cmd = ["cmake", "-S", ".", "-B", str(build_dir), f"-DCMAKE_BUILD_TYPE={args.build_type}"]
    if args.generator:
        cmake_cmd.extend(["-G", args.generator])
    run(cmake_cmd)


def build(args: argparse.Namespace, build_dir: Path) -> None:
    run(["cmake", "--build", str(build_dir)])


def test(build_dir: Path) -> None:
    run(["ctest", "--test-dir", str(build_dir)])


def main() -> None:
    args = parse_args()
    build_dir = Path(args.build_dir)
    configure(args, build_dir)
    build(args, build_dir)
    if args.run_tests:
        test(build_dir)
    print("[ci] Completed on", platform.platform())


if __name__ == "__main__":
    main()
