#!/usr/bin/env python3
"""Package an Abyssforge plugin for distribution."""

from __future__ import annotations

import argparse
import json
import shutil
import tarfile
from pathlib import Path


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("plugin", type=Path, help="Path to plugin directory")
    parser.add_argument("--output", type=Path, default=None, help="Output archive path")
    parser.add_argument("--metadata", type=Path, default=None, help="Optional metadata JSON file")
    parser.add_argument("--vr", action="store_true", help="Mark plugin as VR compatible")
    return parser.parse_args()


def load_metadata(path: Path | None) -> dict:
    if path is None:
        return {}
    return json.loads(path.read_text())


def main() -> None:
    args = parse_args()
    plugin_dir = args.plugin.resolve()
    if not plugin_dir.exists():
        raise FileNotFoundError(plugin_dir)

    metadata = load_metadata(args.metadata)
    metadata.setdefault("name", plugin_dir.name)
    metadata.setdefault("version", "0.1.0")
    metadata["vr_compatible"] = args.vr

    output = args.output or plugin_dir.with_suffix(".tar.gz")
    with tarfile.open(output, "w:gz") as archive:
        for path in plugin_dir.rglob("*"):
            archive.add(path, arcname=path.relative_to(plugin_dir))
        info = tarfile.TarInfo("metadata.json")
        encoded = json.dumps(metadata, indent=2).encode()
        info.size = len(encoded)
        archive.addfile(info, io.BytesIO(encoded))

    print(f"Packaged plugin: {output}")


if __name__ == "__main__":
    import io  # Imported lazily to keep load time low

    main()
