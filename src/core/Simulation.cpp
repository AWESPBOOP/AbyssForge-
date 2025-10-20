#include "abyssforge/core/Simulation.h"

#include <utility>

namespace abyssforge::core {

SimulationController::SimulationController() = default;
SimulationController::~SimulationController() = default;

void SimulationController::configureGenerator(PlanetGeneratorSettings settings)
{
    m_generatorSettings = std::move(settings);
}

PlanetMetadata SimulationController::generatePlanet()
{
    PlanetGenerator generator{m_generatorSettings};
    return generator.generate();
}

void SimulationController::configurePhysicsBodies(std::vector<RigidBodyState> bodies)
{
    m_physics.setBodies(std::move(bodies));
}

void SimulationController::runPhysics(double durationSeconds, double stepSeconds)
{
    m_history.clear();
    m_physics.simulate(durationSeconds, stepSeconds, [&](const SimulationStepResult &step) {
        m_history.push_back(step);
    });
}

} // namespace abyssforge::core
