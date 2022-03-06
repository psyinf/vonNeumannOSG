#include <BehaviorConf.h>
#include <nlohmann/json.hpp>

namespace nsConfig
{

// a simple struct to model an entity
struct SceneConfig
{
    std::string               name;
    std::string               defaultEntity;
    size_t                    numDrones = 0;
    float                     sceneSize = 1000.0f;
    std::vector<BehaviorConf> sceneBehaviors;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SceneConfig, name, defaultEntity, numDrones, sceneSize, sceneBehaviors)
} // namespace nsConfig
