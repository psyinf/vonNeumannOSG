#include "PluginBase.h"
#include <array>
#include <format>
#include <functional>
#include <stdexcept>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using namespace common;
std::string FormatErrorMessage(const DWORD errorCode)
{
    std::array<char, 512> message;

    FormatMessage(
                FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                nullptr,
                errorCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                reinterpret_cast<LPSTR>(message.data()),
                message.size(),
                nullptr);
 
    return std::string(message.begin(), message.end());
}

PLUGIN_API
PluginBase::PluginBase(const std::string& path)
    :path(path)
{
    HMODULE handle;
    // Try to load the plugin as a dynamic library
    handle = ::LoadLibraryEx(path.c_str(), nullptr, 0x00000000);

    if (!handle)
    {
        DWORD       error        = ::GetLastError();
        std::string last_err_str = FormatErrorMessage(error);

        last_err_str.append(" ( ");
        last_err_str.append(std::to_string(error));
        last_err_str.append(" )");
        throw std::invalid_argument(std::format("Could not load '{}'.\nError reported: {}",path, last_err_str));
    }
    //TODO:move to generic list or use introspection
    if (::GetProcAddress(handle, "getInfo"))
    {
        getInfoFunction = std::bind_front(reinterpret_cast<void (*)(PluginInfo&)>(::GetProcAddress(handle, "getInfo")));
    }
    if (!getInfoFunction)
    {
        reportMissingInterface(path, "getInfo");
        
    }

    dllHandle = handle;
}

void PluginBase::reportMissingInterface(const std::string& path,const std::string& name) const
{
    throw std::invalid_argument(std::format("Plugin at '{}' is not a valid plugin (Missing '{}' interface)", path, name));
}

PLUGIN_API void PluginBase::getInfo(PluginInfo& info) const
{
    getInfoFunction(info); 
}

PLUGIN_API PluginBase::~PluginBase()
{
   
    if (dllHandle.has_value())
    {
        // TODO: check effects if dll is unloaded due to error
        PluginInfo info;
        getInfo(info);
        if (!info.dontUnload)
        {
            ::FreeLibrary(std::any_cast<HMODULE>(dllHandle));
        }
        else
        {
            // TODO: log that dll was retained
        }
    }

}
