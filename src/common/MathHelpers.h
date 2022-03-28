#pragma once
#include <osg/Quat>

#include <ostream>
namespace common
{

inline osg::Vec3d makeVec(double v)
{
    return osg::Vec3d(v, v, v);
}


} // namespace common

inline std::ostream& operator<<(std::ostream& os, const osg::Quat& q)
{
    os << q[0] << ", " << q[1] << ", " << q[2] << ", " << q[3];
    return os;
}