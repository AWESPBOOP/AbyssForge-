#pragma once

#include "abyssforge/core/PlanetMetadata.h"

#include <functional>
#include <optional>

namespace abyssforge::core {

struct PlanetGeneratorSettings {
    std::uint64_t seed{0};
    double targetRadiusKm{6371.0};
    double targetMassKg{5.972e24};
    double starLuminositySunUnits{1.0};
    double starAgeMyr{4500.0};
    double orbitalDistanceAU{1.0};
    double gasFraction{0.0};
    double waterFraction{0.71};
    bool enableBiosphere{true};
};

class PlanetGenerator {
public:
    using ProgressCallback = std::function<void(std::string_view stage, double progress)>;

    explicit PlanetGenerator(PlanetGeneratorSettings settings);

    [[nodiscard]] const PlanetGeneratorSettings &settings() const noexcept { return m_settings; }

    PlanetMetadata generate(ProgressCallback progress = {});

private:
    PlanetGeneratorSettings m_settings;
};

} // namespace abyssforge::core
