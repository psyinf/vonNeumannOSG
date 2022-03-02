#include <PluginBase.h>



namespace entities
{
class EntityBehaviorRegistry;

class EntityBehaviorPlugin : public common::PluginBase
{
public:
    explicit EntityBehaviorPlugin(const std::string& plugin_file_path);

    __declspec(dllexport) bool registerBehavior(EntityBehaviorRegistry& entities);

private:
    std::function<int(EntityBehaviorRegistry&)> registerBehaviorFn;


    
};
} // namespace entites