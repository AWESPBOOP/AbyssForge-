cmake_minimum_required(VERSION 3.16)
project(AbyssforgePlanetarySandbox VERSION 0.1.0 LANGUAGES CXX)

option(ABYSSFORGE_BUILD_TESTS "Build unit and integration tests" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
add_subdirectory(plugins/example_destruction)

if(ABYSSFORGE_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

install(EXPORT AbyssforgeTargets
        FILE AbyssforgeTargets.cmake
        NAMESPACE Abyssforge::
        DESTINATION lib/cmake/Abyssforge)

include(CPack)
