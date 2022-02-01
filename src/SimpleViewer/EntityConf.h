#pragma once
#include <nlohmann/json.hpp>

namespace nsEntities {
struct BehaviorConf{
	std::string name;
	nlohmann::json conf;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BehaviorConf, name, conf)

struct EntityConf {
	std::vector<std::string> models;
	std::vector<BehaviorConf> behaviors;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EntityConf, models, behaviors)

}