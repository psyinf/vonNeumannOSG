#include "EntityManager.h"
#include <EntityBehaviorPlugin.h>
#include <EntityBehaviorRegistry.h>
using namespace entities;

EntityManager::EntityManager()
    : behaviorRegistry(std::make_unique<EntityBehaviorRegistry>())
{
    pluginManager->scanForPlugins("plugins");
    //
    for (auto plugin : pluginManager->getPluginList())
    {
        plugin.second->registerBehavior(*behaviorRegistry);
    }
}

entities::EntityBehaviorRegistry& EntityManager::getBehaviorRegistry()
{
    return *behaviorRegistry;
}
