# Abyssforge Alpha 0.1 Windows Release

The prebuilt binary artifact for Windows is not stored in this repository. To generate the `Abyssforge-Alpha-0.1-Windows.zip` package locally, follow these steps:

1. Ensure the project dependencies are installed (see the root `README.md` for platform-specific setup).
2. Build the project in release mode:
   ```bash
   ./scripts/auto_compile.sh --build-type Release --build-dir build/release/windows
   ```
3. Package the Windows release (from a Windows environment or a cross-compiling toolchain) using the helper script:
   ```bash
   python scripts/package_release.py \
     --platform windows-x64 \
     --version 0.1.0 \
     --build-dir build/release/windows \
     --output-dir releases/alpha-0.1/windows
   ```
4. The script emits the `Abyssforge-Alpha-0.1-Windows.zip` archive alongside an updated checksum in `manifest.json`.
5. Distribute the generated archive externally (e.g., GitHub Releases) to share the prebuilt binary.

The `manifest.json` file documents the expected artifact name, build configuration, and release notes to accompany the externally hosted download.
