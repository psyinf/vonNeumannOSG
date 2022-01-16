#include <nlohmann/json.hpp>

namespace nsEntities {
struct EntityConf {
	std::vector<std::string> models;
	std::vector<std::string> behaviors;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EntityConf, models, behaviors)

}