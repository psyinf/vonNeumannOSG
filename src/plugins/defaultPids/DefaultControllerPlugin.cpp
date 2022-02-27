#include <PluginBase.h>
#include <Entities.h>

#define CONTROLLER_PLUGIN_API _declspec(dllexport)

extern "C" CONTROLLER_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = "DefaultPIDControllers";
}




/// Tells us to register our functionality to an engine kernel
extern "C" CONTROLLER_PLUGIN_API void registerPlugin(entities::Entities& entities)
{
    try
    {
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
