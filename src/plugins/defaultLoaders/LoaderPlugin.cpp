#include <PluginBase.h>

#define LOADER_PLUGIN_API _declspec(dllexport)

extern "C" LOADER_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = "DefaultLoaderPlugins";
    info.dontUnload = true; //don't unload due to OSG cache references to objects created in ReaderWriterPlugins
}
