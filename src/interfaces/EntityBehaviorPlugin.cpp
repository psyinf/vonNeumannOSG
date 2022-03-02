#include "EntityBehaviorPlugin.h"

#include <stdexcept>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using namespace entities;


EntityBehaviorPlugin::EntityBehaviorPlugin(const std::string& plugin_file_path)
    : common::PluginBase(plugin_file_path)
{
    try
    {
        HINSTANCE handle = std::any_cast<HINSTANCE>(getHandle());

        if (::GetProcAddress(handle, "registerPlugin"))
        {
            registerBehaviorFn = std::bind_front(reinterpret_cast<int (*)(EntityBehaviorRegistry&)>(::GetProcAddress(handle, "registerPlugin")));
        }

        // If the functions aren't found, we're going to assume this is
        // a plain simple DLL and not one of our plug-ins
        if (!registerBehaviorFn)
        {
            throw std::runtime_error(std::string("'") + plugin_file_path + "' is not a valid plug-in");
        }
        // check for version incompatibilities
    }
    catch (const std::exception& e)
    {
        throw e;
    }
}


bool EntityBehaviorPlugin::registerBehavior(EntityBehaviorRegistry& registry)
{
    if (registerBehaviorFn)
    {
        registerBehaviorFn(registry);
        return true;
    }
    return false;
}
