#pragma once
#include <memory>
#include <PluginManager.h>
#include "PluginBase.h"

namespace entities
{

class EntityBehaviorRegistry;
class EntityBehaviorPlugin;

/**
 * 
 */
class EntityManager
{
    using PluginManager = common::PluginManager<entities::EntityBehaviorPlugin, common::PluginInfo>;

public :
    EntityManager();
    ~EntityManager() = default;
    EntityBehaviorRegistry& getBehaviorRegistry();

private:
    std::unique_ptr<EntityBehaviorRegistry> behaviorRegistry;
    std::unique_ptr<PluginManager>  pluginManager = std::make_unique<PluginManager>();
};
} // namespace entities
