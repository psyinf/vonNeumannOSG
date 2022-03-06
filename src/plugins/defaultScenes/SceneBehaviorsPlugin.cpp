#include "SceneBehaviors.h"

#include <boost/functional/factory.hpp>

#include <EntityBehavior.h>
#include <EntityBehaviorRegistry.h>
#include <EntityManager.h>
#include <PluginBase.h>


#define SCENE_BEHAVIOR_PLUGIN _declspec(dllexport)

extern "C" SCENE_BEHAVIOR_PLUGIN void getInfo(common::PluginInfo& info)
{
    info.name = "SceneBehaviorsPlugin";
}

extern "C" SCENE_BEHAVIOR_PLUGIN void registerPlugin(entities::EntityBehaviorRegistry& registry)
{
    try
    {
        registry.registerPrototype("reflector", boost::factory<entities::Reflector*>());
        registry.registerPrototype("torusificator", boost::factory<entities::Torusifator*>());
    }
    catch (const std::exception& e)
    {
        // TODO: log
        // throw;
        // core.logError(std::string("Unable to register DISSystem :") + std::string(e.what()), __FUNCTION__);
    }
}
