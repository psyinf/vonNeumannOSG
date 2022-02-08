#pragma once
#include <nlohmann/json.hpp>

namespace nsEntities {
struct BehaviorConf{
	std::string type;
	nlohmann::json conf;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(BehaviorConf, type, conf)

struct EntityConf {
	std::string type;
	std::vector<std::string> models;
	std::vector<BehaviorConf> behaviors;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EntityConf,type, models, behaviors)

}