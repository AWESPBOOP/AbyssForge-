#pragma once

#include "abyssforge/plugin/Plugin.h"

#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

namespace abyssforge::plugin {

struct RegisteredTool {
    std::string name;
    std::string description;
};

class PluginRegistry : public PluginContext {
public:
    static PluginRegistry &instance();

    void loadPlugin(std::shared_ptr<Plugin> plugin);

    const std::vector<RegisteredTool> &destructionTools() const noexcept { return m_destructionTools; }
    const std::vector<RegisteredTool> &generators() const noexcept { return m_generators; }

    void registerDestructionTool(std::string name, std::string description) override;
    void registerGenerator(std::string name, std::string description) override;

private:
    PluginRegistry() = default;

    std::mutex m_mutex;
    std::vector<std::shared_ptr<Plugin>> m_plugins;
    std::vector<RegisteredTool> m_destructionTools;
    std::vector<RegisteredTool> m_generators;
};

} // namespace abyssforge::plugin
