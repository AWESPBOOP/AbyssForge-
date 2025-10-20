#include "abyssforge/core/PlanetGenerator.h"
#include "abyssforge/core/PlanetMetadata.h"

#include "thirdparty/doctest/doctest.h"

using namespace abyssforge::core;

DOCTEST_TEST_CASE(test_deterministic_generation)
{
    PlanetGeneratorSettings settings;
    settings.seed = 123456789ULL;

    PlanetGenerator generatorA{settings};
    PlanetGenerator generatorB{settings};

    const auto planetA = generatorA.generate();
    const auto planetB = generatorB.generate();

    DOCTEST_CHECK(planetA.seed == planetB.seed);
    DOCTEST_CHECK(planetA.radiusKm == planetB.radiusKm);
    DOCTEST_CHECK(planetA.massKg == planetB.massKg);
    DOCTEST_CHECK(planetA.atmosphereComposition.size() == planetB.atmosphereComposition.size());
}
