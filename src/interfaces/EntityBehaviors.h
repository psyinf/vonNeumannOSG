#pragma once
#include "EntityBehavior.h"

#include <memory>
#include <unordered_map>


namespace entities
{
class Entity;

class EntityBehaviors
{
public:
    void add(const std::string& name, std::shared_ptr<BehaviorBase> behaviorBase);

    std::shared_ptr<BehaviorBase> get(const std::string& name) const;

    virtual void frame(Entity& entity, FrameTime frameTime);

private:
    std::map<std::string, std::shared_ptr<BehaviorBase>> behaviors;
};

} // namespace entities