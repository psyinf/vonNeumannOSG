#pragma once
#include <osg/Vec3d>

#include <PositionAttitudeConf.h>
#include <nlohmann/json.hpp>
namespace nsConfig
{
struct Marker
{
    bool                 enabled = true;
    std::string          model;
    PositionAttitudeConf pat;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Marker, enabled, model, pat)

} // namespace nsConfig