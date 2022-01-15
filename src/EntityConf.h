#include <nlohmann/json.hpp>

namespace nsEntities {
struct EntityConf {
	std::vector<std::string> models;

};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(EntityConf, models)

}