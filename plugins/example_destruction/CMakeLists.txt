add_library(example_destruction MODULE ExampleDestructionPlugin.cpp)

target_include_directories(example_destruction
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(example_destruction PRIVATE abyssforge)

set_target_properties(example_destruction PROPERTIES
    OUTPUT_NAME "ExampleDestruction"
)
