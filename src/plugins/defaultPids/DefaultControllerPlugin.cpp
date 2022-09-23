#include "controllers/goto/GotoController.h"
#include "controllers/orientation/OrientationController.h"
#include "controllers/position/PositionController.h"

#include <boost/functional/factory.hpp>

#include <EntityBehavior.h>
#include <EntityBehaviorRegistry.h>
#include <EntityManager.h>
#include <PluginBase.h>


#define CONTROLLER_PLUGIN_API _declspec(dllexport)

extern "C" CONTROLLER_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = "DefaultPIDController";
}

extern "C" CONTROLLER_PLUGIN_API void registerPlugin(entities::EntityBehaviorRegistry& registry)
{
    try
    {
        registry.registerPrototype("position", boost::factory<PositionController*>());
        registry.registerPrototype("goto", boost::factory<GotoController*>());
        registry.registerPrototype("orientation", boost::factory<OrientationController*>());
    }
    catch (const std::exception& e)
    {
        // TODO: log
        // throw;
    }
}
