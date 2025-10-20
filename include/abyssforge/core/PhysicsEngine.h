#pragma once

#include "abyssforge/core/PlanetMetadata.h"

#include <array>
#include <functional>
#include <vector>

namespace abyssforge::core {

struct RigidBodyState {
    std::array<double, 3> position{};
    std::array<double, 3> velocity{};
    double mass{1.0};
};

struct SimulationStepResult {
    double timeSeconds{0.0};
    std::vector<RigidBodyState> bodies;
};

class PhysicsEngine {
public:
    using IntegratorCallback = std::function<void(const SimulationStepResult &)>;

    void setBodies(std::vector<RigidBodyState> bodies);
    void simulate(double durationSeconds, double stepSeconds, IntegratorCallback callback);

private:
    std::vector<RigidBodyState> m_bodies;
};

} // namespace abyssforge::core
