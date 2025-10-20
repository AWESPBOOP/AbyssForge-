#include "abyssforge/core/PhysicsEngine.h"

#include <algorithm>
#include <cmath>

namespace abyssforge::core {

namespace {
constexpr double kGravitationalConstant = 6.67430e-11;

std::array<double, 3> vectorSubtract(const std::array<double, 3> &a, const std::array<double, 3> &b)
{
    return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

std::array<double, 3> vectorAdd(const std::array<double, 3> &a, const std::array<double, 3> &b)
{
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

std::array<double, 3> vectorScale(const std::array<double, 3> &a, double scale)
{
    return {a[0] * scale, a[1] * scale, a[2] * scale};
}

} // namespace

void PhysicsEngine::setBodies(std::vector<RigidBodyState> bodies)
{
    m_bodies = std::move(bodies);
}

void PhysicsEngine::simulate(double durationSeconds, double stepSeconds, IntegratorCallback callback)
{
    const std::size_t steps = static_cast<std::size_t>(std::ceil(durationSeconds / stepSeconds));
    auto bodies = m_bodies;

    double currentTime = 0.0;
    for (std::size_t step = 0; step < steps; ++step) {
        std::vector<std::array<double, 3>> accelerations(bodies.size(), {0.0, 0.0, 0.0});

        for (std::size_t i = 0; i < bodies.size(); ++i) {
            for (std::size_t j = 0; j < bodies.size(); ++j) {
                if (i == j) {
                    continue;
                }
                auto diff = vectorSubtract(bodies[j].position, bodies[i].position);
                const double distanceSq = diff[0] * diff[0] + diff[1] * diff[1] + diff[2] * diff[2] + 1e-9;
                const double invDistance = 1.0 / std::sqrt(distanceSq);
                const double invDistanceCube = invDistance * invDistance * invDistance;
                const double force = kGravitationalConstant * bodies[j].mass * invDistanceCube;
                accelerations[i] = vectorAdd(accelerations[i], vectorScale(diff, force));
            }
        }

        for (std::size_t i = 0; i < bodies.size(); ++i) {
            bodies[i].velocity = vectorAdd(bodies[i].velocity, vectorScale(accelerations[i], stepSeconds));
            bodies[i].position = vectorAdd(bodies[i].position, vectorScale(bodies[i].velocity, stepSeconds));
        }

        currentTime += stepSeconds;

        if (callback) {
            callback({currentTime, bodies});
        }
    }

    m_bodies = std::move(bodies);
}

} // namespace abyssforge::core
