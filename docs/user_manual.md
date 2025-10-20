# Abyssforge User Manual

Welcome to **Abyssforge: Planetary Sandbox**. This manual introduces the application workflow, core tools, and accessibility features. The current build focuses on deterministic generation scaffolding while the UI and rendering layers are still under construction.

## 1. Installation

1. Download the platform-specific installer from the Releases page (coming soon) or build from source via CMake.
2. Launch the Abyssforge launcher. Choose GPU backend (Vulkan/DirectX/Metal) and optional VR mode.
3. Configure default asset cache directory. A first-run benchmark will calibrate LOD tiers.

## 2. Quick start tour

1. **Create or load a scenario**: Select *Generate Planet* and enter a seed. Adjust sliders for stellar type, radius, water fraction, and biosphere options.
2. **Explore**: Switch between *System Map*, *Surface Explorer*, and *World Atlas* views. Use WASD + mouse to fly, and press `Tab` to toggle cinematic camera anchors.
3. **Simulate**: Time controls live at the bottom. Drag the logarithmic time wheel or press `[` `]` to halve/double the simulation rate. Pause with `Space`.
4. **Destruction toolkit**: Open the *Forge Tools* panel (`F`). Drag-and-drop events such as *Asteroid Impact*, *Antimatter Burst*, or *Point Singularity* onto the planet. Adjust entry vector, yield, and detonation altitude.
5. **Analyze**: The telemetry HUD tracks thermal flux, mass loss, atmosphere escape, and biosphere survival probability. Use the timeline scrubber to jump to checkpoints or branch alternate outcomes.

## 3. Accessibility

- **Colorblind palettes**: Toggle between protanopia, deuteranopia, and tritanopia palettes.
- **UI scaling**: Set global scale from 50%–250%.
- **Motion comfort**: Enable *VR-lite* with restricted acceleration and comfort vignette.
- **Localization**: Text resources are UTF-8 JSON bundles; contribute translations via the localization toolkit (see docs/guides/extensibility.md).

## 4. Saving and sharing

- *Scenario Save*: Captures seed, overrides, simulation checkpoints, and destruction events.
- *Replay Export*: Generates deterministic timeline bundles for replays or cinematic capture.
- *Asset Export*: Use the exporter panel to bake heightmaps (EXR), texture atlases (TIF), and mesh LODs (OBJ/FBX).

## 5. Troubleshooting

| Issue | Resolution |
|-------|------------|
| Simulation desync in multiplayer | Ensure all participants run identical plugin sets and seeds. Use deterministic replay verification before branching. |
| GPU backend fails to initialize | Switch to CPU fallback in settings. Capture logs from `%APPDATA%/Abyssforge/logs` (Windows) or `~/Library/Application Support/Abyssforge/logs` (macOS/Linux). |
| VR comfort issues | Lower frame reprojection rate or use VR-lite mode. |

## 6. Support

Visit the community hub at `https://abyssforge.community` (placeholder). Submit bug reports via GitHub Issues with logs and reproduction seeds.
