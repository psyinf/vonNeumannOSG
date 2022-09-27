#include "Flatticator.h"
#include "SceneBehaviors.h"

#include <boost/functional/factory.hpp>

#include <EntityBehavior.h>
#include <EntityBehaviorRegistry.h>
#include <EntityManager.h>
#include <PluginBase.h>


#define SCENE_BEHAVIOR_PLUGIN _declspec(dllexport)
const static std::string              pluginName = "SceneBehaviorsPlugin";

extern "C" SCENE_BEHAVIOR_PLUGIN void getInfo(common::PluginInfo& info)
{
    info.name = pluginName;
}

extern "C" SCENE_BEHAVIOR_PLUGIN void registerPlugin(entities::EntityBehaviorRegistry& registry)
{
    try
    {
        registry.registerPrototype("reflector", boost::factory<entities::Reflector*>());
        registry.registerPrototype("torusificator", boost::factory<entities::Torusifator*>());
        registry.registerPrototype("flatticator", boost::factory<entities::Flatticator*>());
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Error registering plugin " << pluginName << ": " << e.what();
        throw;
    }
}
