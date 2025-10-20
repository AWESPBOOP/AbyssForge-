#pragma once

#include <array>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace abyssforge::core {

struct OrbitalParameters {
    double semiMajorAxisAU{1.0};
    double eccentricity{0.0167};
    double inclinationDeg{0.0};
    double longitudeAscendingNodeDeg{0.0};
    double argumentPeriapsisDeg{0.0};
    double meanAnomalyDeg{0.0};
};

struct AtmosphereLayer {
    std::string gas;
    double partialPressure; // in bar
};

struct ClimateBand {
    double latitudeCenterDeg;
    double meanTemperatureK;
    double precipitationRate;
    double albedo;
};

struct BiosphereDescriptor {
    bool enabled{false};
    double biomassIndex{0.0};
    std::map<std::string, double> biomeDistribution;
};

struct PlanetMetadata {
    std::string name;
    std::uint64_t seed{0};
    double radiusKm{6371.0};
    double massKg{5.972e24};
    double rotationPeriodHours{24.0};
    double axialTiltDeg{23.4};
    double surfaceGravityMs2{9.81};
    double coreRadiusKm{3480.0};
    double mantleThicknessKm{2900.0};
    double crustThicknessKm{35.0};
    std::vector<std::string> tectonicPlates;
    std::vector<ClimateBand> climateBands;
    std::vector<AtmosphereLayer> atmosphereComposition;
    OrbitalParameters orbit;
    BiosphereDescriptor biosphere;
    std::map<std::string, std::string> derivedTextures;
    std::map<std::string, double> diagnostics;
};

PlanetMetadata makeDemoPlanet();

} // namespace abyssforge::core
