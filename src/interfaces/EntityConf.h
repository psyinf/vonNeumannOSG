#pragma once
#include <BehaviorConf.h>
#include <GizmoConf.h>
#include <PositionAttitudeConf.h>
#include <nlohmann/json.hpp>
namespace config
{
struct Model
{
    std::string          model;
    PositionAttitudeConf pat;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Model, model, pat)

struct EntityConf
{
    std::string               type;
    std::vector<Model>        models;
    std::vector<BehaviorConf> behaviors;
    std::vector<Gizmo>        gizmos;
    nlohmann::json            properties;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EntityConf, type, models, behaviors, properties, gizmos)

} // namespace confíg