#include <nlohmann/json.hpp>

namespace nsConfig {

	// a simple struct to model a person
	struct SceneConfig {
		std::string name;
		std::string defaultModel;
		size_t numDrones = 0;
		float sceneSize = 1000.0f;
	};
	
	
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SceneConfig, name, defaultModel, numDrones, sceneSize)
}
