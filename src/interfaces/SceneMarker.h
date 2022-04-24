#pragma once
#include <osg/Vec3d>

#include <nlohmann/json.hpp>
#include <osgJsonSerializer.h>
namespace nsConfig
{
struct Marker
{
    bool        enabled = true;
    std::string model;
    osg::Vec3d  pos;
    osg::Vec3d  scale;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Marker, enabled, model, pos, scale)

} // namespace nsConfig