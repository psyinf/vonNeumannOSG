
#include <BehaviorConf.h>
#include <SceneMarker.h>
#include <nlohmann/json.hpp>


namespace config
{

// a simple struct to model an entity
struct SceneConfig
{
    std::string               name;
    std::string               defaultEntity;
    size_t                    numDrones = 0;
    float                     sceneSize = 1000.0f;
    std::vector<BehaviorConf> sceneBehaviors;
    std::vector<Marker>       markers;
};


NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SceneConfig, name, defaultEntity, numDrones, sceneSize, sceneBehaviors, markers)
} // namespace config
