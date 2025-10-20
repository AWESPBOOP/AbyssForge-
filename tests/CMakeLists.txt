add_executable(abyssforge_tests
    test_planet_generation.cpp
)

target_include_directories(abyssforge_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(abyssforge_tests PRIVATE abyssforge)

add_test(NAME abyssforge.tests COMMAND abyssforge_tests)
