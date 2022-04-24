#pragma once
#include <osg/Quat>

namespace osgext
{

inline osg::Quat::value_type dot(const osg::Quat& lhs, const osg::Quat& rhs)
{
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] + lhs[3] * rhs[3];
}

inline osg::Vec3d normalized(const osg::Vec3d& vec)
{
    osg::Vec3d r = vec;
    r.normalize();
    return r;
}

inline osg::Vec3d normalized(osg::Vec3d&& vec)
{
    osg::Vec3d r = std::move(vec);
    r.normalize();
    return r;
}
} // namespace osgext