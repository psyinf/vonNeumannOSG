#pragma once

#include <any>
#include <functional>
#include <string>

#define PLUGIN_API __declspec(dllexport)

namespace common
{
struct PluginInfo
{
    std::string  name;
    auto        operator<=>(const PluginInfo&) const = default;
};

class PluginBase
{
public:
    using DLLHandle = std::any;

    PLUGIN_API explicit PluginBase(const std::string& path);
    PLUGIN_API virtual ~PluginBase() = default;

    PluginBase(const PluginBase&) = delete;
    PluginBase& operator=(const PluginBase&) = delete;

    PLUGIN_API void getInfo(PluginInfo& info) const;
    void            reportMissingInterface(const std::string& path, const std::string& name) const;

private:
    DLLHandle   dllHandle;
    std::string path;

    std::function<void(PluginInfo&)> getInfoFunction;

   
};


} //namespace 