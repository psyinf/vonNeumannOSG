#pragma once
#include <nlohmann/json.hpp>

namespace entities {
struct BehaviorConf{
	bool enabled = true;
	std::string type;
	nlohmann::json conf;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BehaviorConf, enabled, type, conf)

struct EntityConf {
	std::string					type;
	std::vector<std::string>	models;
	std::vector<BehaviorConf>	behaviors;
    nlohmann::json				properties;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EntityConf,type, models, behaviors, properties)

}