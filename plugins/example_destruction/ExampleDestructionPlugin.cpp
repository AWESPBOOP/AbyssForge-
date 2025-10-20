#include "abyssforge/plugin/Plugin.h"

using namespace abyssforge;

namespace {

class ExampleDestructionPlugin final : public plugin::Plugin {
public:
    std::string_view name() const override { return "Example Destruction"; }
    std::string_view version() const override { return "0.1.0"; }

    void onLoad(plugin::PluginContext &context) override
    {
        context.registerDestructionTool(
            "Example: Controlled Antimatter",
            "Demonstrates how to register a new destruction tool with adjustable yield."
        );
        context.registerGenerator(
            "Example: Custom Planet",
            "Placeholder generator that illustrates plugin registration."
        );
    }
};

} // namespace

extern "C" plugin::Plugin *createPlugin()
{
    static ExampleDestructionPlugin pluginInstance;
    return &pluginInstance;
}
