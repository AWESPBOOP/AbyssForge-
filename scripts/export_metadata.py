#!/usr/bin/env python3
"""Export deterministic planet metadata to JSON."""

import argparse
import json
import subprocess
import tempfile
from pathlib import Path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--seed", type=int, required=True, help="Deterministic seed")
    parser.add_argument("--output", type=Path, required=True, help="Output JSON path")
    parser.add_argument("--build-dir", type=Path, default=Path("build"), help="CMake build directory")
    parser.add_argument("--executable", type=str, default="abyssforge_app", help="Executable name")
    return parser.parse_args()


def run_app(build_dir: Path, executable: str, seed: int) -> str:
    app_path = build_dir / "bin" / executable
    if not app_path.exists():
        raise FileNotFoundError(f"Executable not found: {app_path}. Build the project first.")

    result = subprocess.run([str(app_path), str(seed)], capture_output=True, text=True, check=True)
    return result.stdout


def parse_metadata(stdout: str) -> dict:
    metadata = {}
    for line in stdout.splitlines():
        if ":" not in line:
            continue
        key, value = line.split(":", 1)
        metadata[key.strip()] = value.strip()
    return metadata


def main() -> None:
    args = parse_args()
    stdout = run_app(args.build_dir, args.executable, args.seed)
    metadata = parse_metadata(stdout)
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(json.dumps(metadata, indent=2))
    print(f"Exported metadata to {args.output}")


if __name__ == "__main__":
    main()
