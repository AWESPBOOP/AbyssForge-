# Performance & Benchmarking

To reach the target performance envelope (60 FPS on high-end GPUs, 30 FPS on mid-range), Abyssforge relies on multi-threaded simulation, GPU compute, and adaptive level-of-detail. This document details the profiling workflow and benchmark suite.

## Benchmark harness

`benchmarks/run_microbench.py` orchestrates representative workloads:

1. **Planet bake**: Generates 10 deterministic planets with varying seeds and exports texture atlases.
2. **Collision stress**: Executes 1000-body N-body simulation for 10 minutes of simulated time.
3. **Fragment storm**: Spawns 10,000 debris particles and validates streaming throughput.

The script records frame time statistics, memory usage, and GPU occupancy, outputting CSV and HTML reports under `benchmarks/output/`.

## Profiling tools

- **CPU**: Tracy, VTune, Xcode Instruments, or Windows Performance Analyzer.
- **GPU**: RenderDoc, NVIDIA Nsight, AMD Radeon GPU Profiler, Metal System Trace.
- **Simulation**: Built-in profiler overlay accessible via `F9`.

## LOD strategy

- **Physics LOD**: Adaptive integrator precision based on body significance and proximity to interactions.
- **Visual LOD**: Quad-tree planet tessellation with displacement mapping and screen-space refinement.
- **Atmosphere LOD**: Multiple scattering approximations with quality tiers (Ultra/High/Medium/Low).

## Determinism under optimization

- All optimizations must preserve deterministic ordering of floating-point operations. Use fused multiply-add where hardware matches reference results, or fall back to CPU double precision.
- GPU kernels emit hashed checkpoints that are compared against CPU baselines in debug builds.

## CI integration

- GitHub Actions runs `scripts/ci_build.py` for all platforms.
- Performance regression detection uses rolling medians with ±5% tolerance.
- Benchmarks can be invoked manually: `python benchmarks/run_microbench.py --profile --report`.

## Tips for contributors

- Prefer structure-of-arrays for hot physics paths.
- Batch GPU updates to minimize synchronization.
- Avoid allocations inside per-frame loops.
- Test on multiple GPUs (NVIDIA, AMD, Apple Silicon) and CPUs.
