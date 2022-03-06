#include "PositionController.h"

#include <boost/functional/factory.hpp>

#include <EntityBehavior.h>
#include <EntityBehaviorRegistry.h>
#include <EntityManager.h>
#include <PluginBase.h>


#define CONTROLLER_PLUGIN_API _declspec(dllexport)

extern "C" CONTROLLER_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = "DefaultPIDControllers";
}

extern "C" CONTROLLER_PLUGIN_API void registerPlugin(entities::EntityBehaviorRegistry& registry)
{
    try
    {
        registry.registerPrototype("position", boost::factory<PositionController*>());
    }
    catch (const std::exception& e)
    {
        // TODO: log
        // throw;
    }
}
