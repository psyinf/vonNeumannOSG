#pragma once
#include <PluginManager.h>
#include <PluginBase.h>

using PluginManager = common::PluginManager<common::PluginBase, common::PluginInfo>;

namespace entities{

class Entities
{
    Entities() {
        pluginManager->scanForPlugins("plugins");
    }
    std::unique_ptr<PluginManager> pluginManager = std::make_unique<PluginManager>();
};
	
}