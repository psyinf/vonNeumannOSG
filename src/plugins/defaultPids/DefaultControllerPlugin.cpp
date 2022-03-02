#include <PluginBase.h>
#include "PositionController.h"
#include <EntityBehavior.h>
#include <EntityManager.h>
#include <EntityBehaviorRegistry.h>

#include <boost/functional/factory.hpp>


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
        //add constructor for the module
        //core.getModuleRegistry()->addConstructor("DISSystem", boost::factory<nsDISSystem::DISSystem*>());
    }
    catch (const std::exception& e)
    {
        //TODO: log
        //throw;
        //core.logError(std::string("Unable to register DISSystem :") + std::string(e.what()), __FUNCTION__);
    }
}
