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
    using BehaviorPluginManager = common::PluginManager<entities::EntityBehaviorPlugin, common::PluginInfo>;
    using LoaderPluginManager = common::PluginManager<common::PluginBase, common::PluginInfo>;

public :
    EntityManager();
    ~EntityManager() = default;
    EntityBehaviorRegistry& getBehaviorRegistry();

private:
    std::unique_ptr<EntityBehaviorRegistry> behaviorRegistry;
    std::unique_ptr<BehaviorPluginManager>  behaviorPluginManager = std::make_unique<BehaviorPluginManager>();
    std::unique_ptr<LoaderPluginManager>    loaderPluginManager = std::make_unique<LoaderPluginManager>();
};
} // namespace entities
