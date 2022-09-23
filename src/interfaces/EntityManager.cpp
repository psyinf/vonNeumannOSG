#include "EntityManager.h"
#include <EntityBehaviorPlugin.h>
#include <EntityBehaviorRegistry.h>
using namespace entities;

EntityManager::EntityManager()
    : behaviorRegistry(std::make_unique<EntityBehaviorRegistry>())
{
    behaviorPluginManager->scanForPlugins("plugins", "*Plugin*.dll");
    //
    for (auto plugin : behaviorPluginManager->getPluginList())
    {
        plugin.second->registerBehavior(*behaviorRegistry);
    }
    //only load plugins
    loaderPluginManager->scanForPlugins("plugins", "*Loader*.dll");


}

entities::EntityBehaviorRegistry& EntityManager::getBehaviorRegistry()
{
    return *behaviorRegistry;
}
