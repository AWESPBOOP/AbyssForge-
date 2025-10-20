#include "abyssforge/core/PlanetMetadata.h"

namespace abyssforge::core {

PlanetMetadata makeDemoPlanet()
{
    PlanetMetadata planet;
    planet.name = "Demo Terra";
    planet.seed = 42;
    planet.radiusKm = 6371.0;
    planet.massKg = 5.972e24;
    planet.rotationPeriodHours = 23.93;
    planet.axialTiltDeg = 23.4;
    planet.surfaceGravityMs2 = 9.81;
    planet.coreRadiusKm = 3480.0;
    planet.mantleThicknessKm = 2900.0;
    planet.crustThicknessKm = 35.0;
    planet.tectonicPlates = {"Pacific", "North American", "Eurasian", "African", "Antarctic"};
    planet.climateBands.push_back({0.0, 288.0, 3.0, 0.3});
    planet.atmosphereComposition.push_back({"N2", 0.78});
    planet.atmosphereComposition.push_back({"O2", 0.21});
    planet.atmosphereComposition.push_back({"Ar", 0.009});
    planet.biosphere.enabled = true;
    planet.biosphere.biomassIndex = 0.82;
    planet.biosphere.biomeDistribution = {{"Tropical Rainforest", 0.18}, {"Temperate Forest", 0.25}, {"Desert", 0.2}};
    planet.derivedTextures = {{"albedo", "textures/demo_albedo.exr"}, {"normal", "textures/demo_normal.exr"}};
    planet.diagnostics = {{"mean_surface_temperature_K", 287.0}, {"orbital_period_days", 365.25}};
    return planet;
}

} // namespace abyssforge::core
