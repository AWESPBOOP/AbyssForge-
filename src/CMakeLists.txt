set(SRC_FILES
    core/PlanetGenerator.cpp
    core/PlanetMetadata.cpp
    core/PhysicsEngine.cpp
    core/Simulation.cpp
    plugin/PluginRegistry.cpp
)

add_library(abyssforge STATIC ${SRC_FILES})
target_include_directories(abyssforge
    PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(abyssforge
    PUBLIC ABYSSFORGE_VERSION=\"${PROJECT_VERSION}\"
)

add_library(Abyssforge::abyssforge ALIAS abyssforge)

add_executable(abyssforge_app app/main.cpp)
target_link_libraries(abyssforge_app PRIVATE abyssforge)

install(TARGETS abyssforge abyssforge_app
        EXPORT AbyssforgeTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

