#pragma once

#include "abyssforge/core/PlanetMetadata.h"

#include <string>
#include <string_view>

namespace abyssforge::plugin {

class PluginContext {
public:
    virtual ~PluginContext() = default;

    virtual void registerDestructionTool(std::string name, std::string description) = 0;
    virtual void registerGenerator(std::string name, std::string description) = 0;
};

class Plugin {
public:
    virtual ~Plugin() = default;
    virtual std::string_view name() const = 0;
    virtual std::string_view version() const = 0;
    virtual void onLoad(PluginContext &context) = 0;
};

using CreatePluginFn = Plugin *(*)();

} // namespace abyssforge::plugin
