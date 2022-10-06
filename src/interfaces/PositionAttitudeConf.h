#pragma once
#include <osg/PositionAttitudeTransform>
#include <osg/Vec3d>

#include <nlohmann/json.hpp>
#include <osgJsonSerializer.h>
namespace config
{
struct PositionAttitudeConf
{
    osg::Vec3d         pos;
    osg::Vec3d         scale;
    inline static void from(osg::PositionAttitudeTransform* pat, PositionAttitudeConf patConf)
    {
        pat->setPosition(patConf.pos);
        pat->setScale(patConf.scale);
    }
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PositionAttitudeConf, pos, scale)
} // namespace config