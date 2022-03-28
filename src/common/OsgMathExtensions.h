#pragma once
#include <osg/Quat>

namespace osgExt
{

inline osg::Quat::value_type dot(const osg::Quat& lhs, const osg::Quat& rhs)
{
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] + lhs[3] * rhs[3];
}

} // namespace osgExt