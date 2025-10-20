# Abyssforge — Procedural Planetary Sandbox

> Forge worlds. Break worlds. Learn why.

This repository hosts the reference implementation scaffold for **Abyssforge: Planetary Sandbox**, a cross-platform desktop application focused on procedural planet generation, cinematic destruction tooling, and deterministic astrophysical simulation. The current snapshot establishes an extensible architecture, build system, testing harness, and documentation suite so that future contributors can continue scaling toward the full product vision.

## Project overview

- **Languages & runtime**: Modern C++20 core with optional scripting bindings (Lua/Python bindings planned). GPU backends (Vulkan/Metal/DirectX) and VR mode are designed as modular subsystems.
- **Platforms**: Windows, macOS, Linux. Mobile/VR clients connect through the plugin API.
- **Seeded procedural pipeline**: Deterministic generation for stellar context, planetary structure, surface processes, atmosphere, climate, and biosphere.
- **High-precision physics**: Modular N-body integrators with GPU acceleration paths and CPU fallback.
- **Destruction sandbox**: Configurable tools such as kinetic impacts, exotic energy events, and relativistic phenomena.
- **Extensibility first**: Plugin registry, scripting API, node-graph editor, and robust scenario serialization.

> ⚠️ The current repository focuses on infrastructure and representative stubs. Major rendering, GPU compute, VR, and networking layers are outlined but intentionally minimal. See the [Roadmap](docs/guides/roadmap.md) for the staged delivery plan.

## Getting started

### Prerequisites

- CMake ≥ 3.16
- A C++20 toolchain (MSVC 2022, Clang ≥ 14, or GCC ≥ 11)
- Python ≥ 3.10 for tooling scripts

Optional dependencies (planned future integrations):

- Vulkan SDK 1.3+
- CUDA Toolkit 12+ (Windows/Linux)
- Metal SDK (macOS)

### Configure & build

```bash
cmake -S . -B build -DABYSSFORGE_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```

Artifacts include the `abyssforge_app` CLI prototype and the `example_destruction` plugin module.

### Repository layout

```
include/                # Public headers for the core engine & APIs
src/                    # Engine implementation (core, app, plugins)
plugins/                # Example plugins & SDK entry points
docs/                   # User guides, API references, design specs
scenarios/              # Shareable deterministic scenario bundles
benchmarks/             # Automated performance scripts
scripts/                # Build, packaging, and CI helper scripts
tests/                  # Deterministic unit/integration test suite
```

## Quick demo

Generate a demo planet with seed `12345` and dump summary output:

```bash
./build/bin/abyssforge_app 12345
```

Inspect deterministic metadata for a scenario:

```bash
python scripts/export_metadata.py --seed 12345 --output scenarios/seed_12345.json
```

Run the sample benchmark harness:

```bash
python benchmarks/run_microbench.py
```

## Build helpers

To compile the project with the default release configuration without fetching any additional
dependencies, run the lightweight helper script:

```bash
scripts/auto_compile.sh
```

Pass `--build-type <Config>` (defaults to `Release`) to switch configurations and/or `--build-dir
<path>` to emit artifacts somewhere other than the default `build/` directory.

## Releases

Prebuilt binaries are not stored in the repository to keep the history lightweight. To reproduce
the Windows Alpha 0.1 package locally, follow the step-by-step instructions in
`releases/alpha-0.1/windows/BUILD_FROM_SOURCE.md`. Once generated, host the resulting
`Abyssforge-Alpha-0.1-Windows.zip` archive on your preferred distribution platform (e.g., GitHub
Releases) and reference the accompanying `manifest.json` metadata for checksums and release notes.

## Documentation

- [User Manual](docs/user_manual.md)
- [Scripting API Preview](docs/api/scripting_api.md)
- [Extensibility Guide](docs/guides/extensibility.md)
- [Performance & Benchmarking](docs/guides/performance.md)
- [Roadmap](docs/guides/roadmap.md)
- [Design Overview](docs/guides/design_overview.md)

## Contributing

1. Fork the repository & create a feature branch.
2. Ensure reproducibility by running the deterministic test suite.
3. Submit a PR that includes documentation & tests where applicable.

Please review the [Code of Conduct](docs/CODE_OF_CONDUCT.md) and [Contribution Guide](docs/CONTRIBUTING.md).

## License

Abyssforge is released under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgements

- Procedural geology inspiration from academic work on mantle convection and plate tectonics.
- GPU physics techniques informed by N-body simulation research.
- Atmosphere rendering references from Eric Bruneton and Sébastien Hillaire.
