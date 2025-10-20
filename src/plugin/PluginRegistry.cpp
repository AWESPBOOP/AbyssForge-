#include "abyssforge/plugin/PluginRegistry.h"

namespace abyssforge::plugin {

PluginRegistry &PluginRegistry::instance()
{
    static PluginRegistry registry;
    return registry;
}

void PluginRegistry::loadPlugin(std::shared_ptr<Plugin> plugin)
{
    if (!plugin) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    plugin->onLoad(*this);
    m_plugins.push_back(std::move(plugin));
}

void PluginRegistry::registerDestructionTool(std::string name, std::string description)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_destructionTools.push_back({std::move(name), std::move(description)});
}

void PluginRegistry::registerGenerator(std::string name, std::string description)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_generators.push_back({std::move(name), std::move(description)});
}

} // namespace abyssforge::plugin
