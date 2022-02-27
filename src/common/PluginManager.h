#pragma once



#include <boost/algorithm/string.hpp>
#include <filesystem>
#include <format>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>


namespace common
{


template <class PluginBaseClass, class PluginInfoType>
class PluginManager
{
    using PluginBasePtr = std::shared_ptr<PluginBaseClass>;
    using PluginMap     = std::map<PluginInfoType, PluginBasePtr>;

public:
    PluginManager()
    {
    }
    virtual ~PluginManager() = default;
    
    

    void scanForPlugins(const std::string& path, const std::vector<std::string>& filters)
    {
        for (auto iter = filters.begin(); iter != filters.end(); ++iter)
        {
            scanForPlugins(path, (*iter));
        }
    }

    size_t scanForPlugins(const std::string& path, const std::string& filter = "*.dll")
    {
        size_t      num_loaded = 0;
        std::cout <<  "Scanning for plugins in :" + path;

        for (auto& p : std::filesystem::directory_iterator(path)) /*get directory */
        {
            bool is_debug = false;
#ifdef _DEBUG
            is_debug = true;
#endif
            if (!boost::algorithm::iends_with(p.path().string(), "_d.dll") && is_debug)
            {
                //log(pslog::Level::CONFIG) << "skipping non-debug plugin: " << dir_entry;
                continue;
            }
            else if (boost::algorithm::iends_with(p.path().string(), "_d.dll") && !is_debug)
            {
                //log(pslog::Level::CONFIG) << "skipping debug plugin: " << dir_entry;
                continue;
            }
            else
            {
                try
                {
                    PluginBasePtr  plugin(new PluginBaseClass(p.path().string()));
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
                    std::cout << std::format("Error loading  plugin {}: {}", p.path().string(), e.what()) << std::endl;
                }
            }
        }
        return num_loaded;
    }

    PluginBasePtr getPlugin(const std::string& plugin_name)
    {
        PluginInfoType plugin_info;
        //plugin info type at least needs a key type string
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


} // namespace nsCommon