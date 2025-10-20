# Extensibility Guide

Abyssforge is designed to be extended by modders, studios, and researchers. This guide explains the available extension points and how to package, distribute, and validate custom modules.

## Plugin architecture

- **Binary plugins**: Native modules compiled against the Abyssforge SDK implement the `abyssforge::plugin::Plugin` interface. They can register generators, destruction tools, render passes, or network transports.
- **Scripting plugins**: Lua/Python scripts are sandboxed and loaded dynamically. They expose metadata files describing compatibility and dependencies.
- **Node graph packages**: Procedural generation graphs can be exported/imported as `.forgegraph` files for sharing.

### Lifecycle

1. Discovery: Plugins placed in `AbyssforgePlugins/` (platform dependent) are scanned on launch.
2. Validation: Digital signatures and compatibility constraints are verified.
3. Registration: `Plugin::onLoad` receives a `PluginContext` to register tools, UI panels, or simulation callbacks.
4. Execution: Plugins receive deterministic hooks during simulation and rendering phases.

### Example plugin

See [`plugins/example_destruction`](../../plugins/example_destruction) for a minimal native plugin that registers a new destruction tool. Build it with:

```bash
cmake --build build --target example_destruction
```

## Scripting API

- Scripts run inside deterministic sessions. Side effects (file I/O, networking) must go through provided APIs.
- Each script must declare compatibility metadata in `*.forgeplugin` manifest files.
- Scripts can contribute UI via declarative JSON definitions consumed by the ImGui-based editor.

## Asset pipelines

Abyssforge ships with headless tools to bake planetary data:

| Tool | Description |
|------|-------------|
| `forgeheight` | Generates multi-resolution heightmap pyramids (EXR) from procedural data. |
| `forgenormal` | Builds tangent-space normal maps and curvature textures. |
| `forgelod` | Produces adaptive mesh LODs with quad-tree tessellation. |

All tools accept `--seed` and `--override` parameters for reproducibility.

## Multiplayer mods

- Multiplayer servers operate in authoritative deterministic mode.
- Mods must be installed on server and clients with identical versions.
- Deterministic validation occurs at session join; mismatches cause a graceful fallback to observer mode.

## Distribution

Package plugins with the `scripts/package_plugin.py` helper. It bundles binaries, manifests, documentation, and signature files. Use the `--vr` flag to mark VR-compatible modules.

## Testing

Run `ctest -L plugins` to execute plugin-specific validation suites. Custom plugins should provide integration tests covering determinism contracts.

## Safety guidelines

- Avoid blocking operations on the simulation thread.
- Respect GPU/CPU budget hints when registering heavy compute tasks.
- Document any new destruction tool parameters with units and expected ranges.
