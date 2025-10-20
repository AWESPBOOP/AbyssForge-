#include "abyssforge/core/PlanetGenerator.h"

#include <cmath>
#include <random>

namespace abyssforge::core {

namespace {
constexpr double kPi = 3.14159265358979323846;

std::mt19937_64 createRng(std::uint64_t seed)
{
    return std::mt19937_64{seed};
}

} // namespace

PlanetGenerator::PlanetGenerator(PlanetGeneratorSettings settings)
    : m_settings(settings)
{
}

PlanetMetadata PlanetGenerator::generate(ProgressCallback progress)
{
    if (progress) {
        progress("init", 0.05);
    }

    auto rng = createRng(m_settings.seed);
    std::uniform_real_distribution<double> unit(0.0, 1.0);

    PlanetMetadata planet;
    planet.seed = m_settings.seed;
    planet.name = "Seeded Planet " + std::to_string(m_settings.seed);

    const double radiusJitter = 0.95 + 0.1 * unit(rng);
    planet.radiusKm = m_settings.targetRadiusKm * radiusJitter;
    planet.massKg = m_settings.targetMassKg * std::pow(radiusJitter, 3.0);
    planet.rotationPeriodHours = 6.0 + 24.0 * unit(rng);
    planet.axialTiltDeg = 5.0 + 50.0 * unit(rng);
    planet.surfaceGravityMs2 = (planet.massKg / m_settings.targetMassKg) * 9.81;

    planet.coreRadiusKm = planet.radiusKm * (0.4 + 0.1 * unit(rng));
    planet.mantleThicknessKm = planet.radiusKm - planet.coreRadiusKm - (5.0 + 50.0 * unit(rng));
    planet.crustThicknessKm = 5.0 + 70.0 * unit(rng);

    const int plateCount = 6 + static_cast<int>(unit(rng) * 6.0);
    for (int i = 0; i < plateCount; ++i) {
        planet.tectonicPlates.push_back("Plate_" + std::to_string(i));
    }

    for (int band = -3; band <= 3; ++band) {
        const double latitude = band * 15.0;
        const double temp = 220.0 + 90.0 * std::cos(latitude * kPi / 180.0);
        const double precip = std::max(0.0, 5.0 * std::sin((band + 3) * kPi / 6.0));
        planet.climateBands.push_back({latitude, temp, precip, 0.2 + 0.5 * unit(rng)});
    }

    planet.atmosphereComposition = {
        {"N2", 0.65 + 0.2 * unit(rng)},
        {"O2", 0.15 + 0.1 * unit(rng)},
        {"CO2", 0.0002 + 0.01 * unit(rng)},
        {"H2O", 0.02 + 0.05 * unit(rng)}
    };

    planet.orbit.semiMajorAxisAU = m_settings.orbitalDistanceAU;
    planet.orbit.eccentricity = 0.01 + 0.2 * unit(rng);
    planet.orbit.inclinationDeg = 0.0 + 10.0 * unit(rng);
    planet.orbit.longitudeAscendingNodeDeg = 360.0 * unit(rng);
    planet.orbit.argumentPeriapsisDeg = 360.0 * unit(rng);
    planet.orbit.meanAnomalyDeg = 360.0 * unit(rng);

    if (m_settings.enableBiosphere) {
        planet.biosphere.enabled = true;
        planet.biosphere.biomassIndex = unit(rng);
        planet.biosphere.biomeDistribution = {
            {"Forest", unit(rng)},
            {"Desert", unit(rng)},
            {"Ocean", unit(rng)}
        };
    }

    planet.derivedTextures = {
        {"albedo", "generated://albedo"},
        {"normal", "generated://normal"},
        {"height", "generated://height"}
    };

    planet.diagnostics = {
        {"stellar_luminosity_solar", m_settings.starLuminositySunUnits},
        {"stellar_age_myr", m_settings.starAgeMyr},
        {"water_fraction", m_settings.waterFraction},
        {"gas_fraction", m_settings.gasFraction}
    };

    if (progress) {
        progress("finalize", 1.0);
    }

    return planet;
}

} // namespace abyssforge::core
