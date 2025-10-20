#!/usr/bin/env python3
"""Package a prebuilt release archive for distribution."""
from __future__ import annotations

import argparse
import hashlib
import json
import shutil
from datetime import datetime
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BUILD_DIR = ROOT / "build" / "release" / "windows"
RELEASE_DIR = ROOT / "releases" / "alpha-0.1" / "windows"
ARTIFACT_NAME = "Abyssforge-Alpha-0.1-Windows.zip"


def compute_sha256(path: Path) -> str:
    sha = hashlib.sha256()
    with path.open("rb") as fh:
        for chunk in iter(lambda: fh.read(1024 * 1024), b""):
            sha.update(chunk)
    return sha.hexdigest()


def zip_release(source: Path, destination: Path) -> Path:
    destination.parent.mkdir(parents=True, exist_ok=True)
    if destination.exists():
        destination.unlink()
    archive = shutil.make_archive(str(destination.with_suffix("")), "zip", root_dir=source)
    return Path(archive)


def update_manifest(
    manifest_path: Path,
    checksum: str,
    platform: str,
    version: str,
    created: datetime | None,
) -> None:
    data = json.loads(manifest_path.read_text()) if manifest_path.exists() else {}
    data.update(
        {
            "name": data.get("name", "Abyssforge Alpha 0.1"),
            "platform": platform,
            "version": version,
            "build": data.get("build", "release"),
            "artifact": data.get("artifact", ARTIFACT_NAME),
            "artifact_hosting": data.get("artifact_hosting", "external"),
            "sha256": checksum,
            "created": (created or datetime.utcnow()).isoformat() + "Z",
        }
    )
    manifest_path.write_text(json.dumps(data, indent=2) + "\n")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--platform", default="windows-x64")
    parser.add_argument("--version", default="0.1.0")
    parser.add_argument("--build-dir", type=Path, default=BUILD_DIR)
    parser.add_argument("--output-dir", type=Path, default=RELEASE_DIR)
    parser.add_argument("--artifact-name", default=ARTIFACT_NAME)
    parser.add_argument("--manifest", type=Path, default=RELEASE_DIR / "manifest.json")
    parser.add_argument("--created", type=str, help="ISO timestamp override for manifest metadata")
    args = parser.parse_args()

    created_dt = datetime.fromisoformat(args.created.replace("Z", "")) if args.created else None
    output_path = args.output_dir / args.artifact_name
    artifact = zip_release(args.build_dir, output_path)
    checksum = compute_sha256(artifact)
    update_manifest(args.manifest, checksum, args.platform, args.version, created_dt)
    print(f"Created {artifact} (sha256={checksum})")


if __name__ == "__main__":
    main()
