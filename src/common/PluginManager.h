#pragma once

#include <filesystem>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

namespace common
{
constexpr bool isDebug()
{
    // TODO: move to global helper
    bool is_debug = false;
#ifdef _DEBUG
    is_debug = true;
#endif
    return is_debug;
}

template <class PluginBaseClass, class PluginInfoType>
class PluginManager
{
    using PluginBasePtr = std::shared_ptr<PluginBaseClass>;
    using PluginMap     = std::map<PluginInfoType, PluginBasePtr>;

public:
    PluginManager()          = default;
    virtual ~PluginManager() = default;

    PluginBasePtr makeInstance(const std::filesystem::directory_entry& entry)
    {
        return std::make_shared<PluginBaseClass>(entry.path().string());
    }

    void scanForPlugins(const std::string& path, const std::vector<std::string>& filters)
    {
        std::ranges::for_each(
            filters, [](const auto& filter) { scanForPlugins(path, filter); });
    }

    size_t scanForPlugins(const std::string& path, const std::string& filter = "*.dll")
    {
        size_t num_loaded = 0;
        // std::cout <<  "Scanning for plugins in :" + path;

        for (auto& p : std::filesystem::directory_iterator(path)) /*get directory */
        {
            auto file_path = p.path().filename().replace_extension("").string();
            file_path | std::ranges::views::transform([](auto c) { return std::toupper(c); });
           

            if (!file_path.ends_with("_d") && isDebug())
            {
                // log(pslog::Level::CONFIG) << "skipping non-debug plugin: " << dir_entry;
                continue;
            }
            else if (file_path.ends_with("_d") && !isDebug())
            {
                // log(pslog::Level::CONFIG) << "skipping debug plugin: " << dir_entry;
                continue;
            }
            else
            {
                try
                {
                    auto           plugin = makeInstance(p);
                    PluginInfoType plugin_info;
                    plugin->getInfo(plugin_info);
                    if (!mPlugins.count(plugin_info))
                    {
                        std::cout << std::format("Found plugin {} [{}]", p.path().filename().string(), plugin_info.name) << std::endl;
                        mPlugins[plugin_info] = plugin;
                        ++num_loaded;
                    }
                    else
                    {
                        // std::cout << std::format("Skipping plugin {} [{}], already registered.", p.path().filename().string(), plugin_info.name) << std::endl;
                    }
                }
                catch (const std::exception& e)
                {
                    std::cout << std::format("Error loading plugin {}: {}", p.path().string(), e.what()) << std::endl;
                }
            }
        }
        return num_loaded;
    }


    PluginBasePtr getPlugin(const std::string& plugin_name)
    {
        PluginInfoType plugin_info;
        // plugin info type at least needs a key type string
        plugin_info.name = plugin_name;
        if (mPlugins.count(plugin_info))
        {
            return (mPlugins[plugin_info]);
        }
    }

    auto getPluginList() -> PluginMap
    {
        return mPlugins;
    }

private:
    PluginMap mPlugins;
};


} // namespace common