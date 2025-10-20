#pragma once

#include "abyssforge/core/PhysicsEngine.h"
#include "abyssforge/core/PlanetGenerator.h"

#include <mutex>
#include <optional>
#include <thread>

namespace abyssforge::core {

class SimulationController {
public:
    SimulationController();
    ~SimulationController();

    void configureGenerator(PlanetGeneratorSettings settings);
    PlanetMetadata generatePlanet();

    void configurePhysicsBodies(std::vector<RigidBodyState> bodies);
    void runPhysics(double durationSeconds, double stepSeconds);

    [[nodiscard]] const std::vector<SimulationStepResult> &history() const noexcept { return m_history; }

private:
    PlanetGeneratorSettings m_generatorSettings{};
    PhysicsEngine m_physics;
    std::vector<SimulationStepResult> m_history;
};

} // namespace abyssforge::core
