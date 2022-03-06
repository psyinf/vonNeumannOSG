#pragma once
#include <BehaviorConf.h>
#include <nlohmann/json.hpp>
namespace entities
{


struct EntityConf
{
    std::string                         type;
    std::vector<std::string>            models;
    std::vector<nsConfig::BehaviorConf> behaviors;
    nlohmann::json                      properties;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EntityConf, type, models, behaviors, properties)

} // namespace entities