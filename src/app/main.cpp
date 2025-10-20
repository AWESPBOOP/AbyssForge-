#include "abyssforge/core/Simulation.h"
#include "abyssforge/plugin/PluginRegistry.h"

#include <iostream>

using namespace abyssforge;

int main(int argc, char **argv)
{
    std::uint64_t seed = 42;
    if (argc > 1) {
        seed = std::stoull(argv[1]);
    }

    core::SimulationController simulation;
    simulation.configureGenerator(core::PlanetGeneratorSettings{
        .seed = seed,
        .targetRadiusKm = 6371.0,
        .targetMassKg = 5.972e24,
        .starLuminositySunUnits = 1.0,
        .starAgeMyr = 4500.0,
        .orbitalDistanceAU = 1.0,
        .gasFraction = 0.0,
        .waterFraction = 0.71,
        .enableBiosphere = true,
    });

    const auto planet = simulation.generatePlanet();

    std::cout << "Abyssforge Planetary Sandbox Prototype\n";
    std::cout << "Seed: " << planet.seed << '\n';
    std::cout << "Name: " << planet.name << '\n';
    std::cout << "Radius (km): " << planet.radiusKm << '\n';
    std::cout << "Mass (kg): " << planet.massKg << '\n';
    std::cout << "Axial tilt (deg): " << planet.axialTiltDeg << '\n';
    std::cout << "Tectonic plates: " << planet.tectonicPlates.size() << '\n';

    simulation.configurePhysicsBodies({
        {{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, planet.massKg},
        {{4.2e7, 0.0, 0.0}, {0.0, 1022.0, 0.0}, 7.35e22}
    });

    simulation.runPhysics(60.0, 1.0);

    std::cout << "Physics history steps: " << simulation.history().size() << '\n';

    auto &registry = plugin::PluginRegistry::instance();
    registry.registerDestructionTool("Prototype Impact", "Simple kinetic strike placeholder");

    std::cout << "Registered destruction tools: " << registry.destructionTools().size() << '\n';

    return 0;
}
