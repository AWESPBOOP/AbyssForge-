# Scripting API (Preview)

Abyssforge exposes a high-level scripting API to empower modders, educators, and researchers. The initial bindings target **Python 3.10+** and **Lua 5.4**, with identical semantics across languages. All scripting operates on deterministic data structures and is sandboxed to prevent non-deterministic side effects.

## Core concepts

| Concept | Description |
|---------|-------------|
| `PlanetHandle` | Lightweight reference to a generated planet and its simulation state. |
| `EventTimeline` | Immutable sequence of destruction / simulation events. |
| `FragmentField` | GPU-backed particle dataset representing debris fragments. |
| `RendererBridge` | Provides hooks for custom rendering passes or cinematic capture. |

## Python example

```python
from abyssforge import scripting

with scripting.session(seed=12345) as session:
    planet = session.generate_planet(radius_km=6371, water_fraction=0.7)

    asteroid = session.create_impactor(
        name="Research Impact",
        diameter_km=12,
        composition="Fe",
        velocity_kms=20,
        latitude_deg=30,
        longitude_deg=-45,
        angle_deg=45,
    )

    timeline = session.schedule_event(asteroid, time_offset_seconds=0)
    session.advance(time_scale=1000.0, duration_seconds=60 * 60)

    metrics = planet.sample_global_metrics([
        "atmosphere_mass_loss", "surface_temperature_mean", "biosphere_survival_probability"
    ])

    session.export(
        output_dir="scenarios/research_impact",
        include_fragments=True,
        include_video=True,
    )
```

## Lua example

```lua
local session = abyssforge.session({ seed = 987654321 })
local planet = session:generate_planet({ radius_km = 9000, gas_fraction = 0.1 })

local antimatter = session:create_energy_event({
    label = "Controlled Antimatter",
    yield_megatons = 1000,
    altitude_km = 50,
})

session:schedule_event(antimatter, { time_offset_seconds = 5 })
session:advance({ duration_seconds = 3600, time_scale = 1e6 })

session:export({ path = "scenarios/antimatter_demo" })
session:close()
```

## Determinism contracts

- Scripts must avoid querying wall-clock time or non-deterministic RNG.
- Abyssforge provides seed-locked random streams per subsystem.
- Networking or disk I/O is mediated by the sandbox runtime and recorded in scenario metadata.

## Extensibility hooks

- `session.register_generator(callable)` — adds a custom procedural node to the pipeline graph.
- `session.register_renderer(stage, callable)` — injects GPU passes at defined hooks.
- `session.register_tool(name, callback)` — expose new destruction controls to the UI.

Detailed API reference will be generated from Doxygen + Sphinx (see `docs/api/reference` in future releases).
