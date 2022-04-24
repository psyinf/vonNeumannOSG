#pragma once
#include <osg/Vec3>

using json = nlohmann::json;
namespace osg
{

void to_json(json& j, const Vec3d& p)
{
    j = json::array();
    j.push_back(p[0]);
    j.push_back(p[1]);
    j.push_back(p[2]);
}

void from_json(const json& j, Vec3d& p)
{
    j[0].get_to(p[0]);
    j[1].get_to(p[1]);
    j[2].get_to(p[2]);
}
} // namespace osg