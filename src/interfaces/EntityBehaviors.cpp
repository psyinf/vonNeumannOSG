#include "EntityBehavior.h"
#include "EntityBehaviors.h"
#include <algorithm>

using namespace entities;

void EntityBehaviors::add(const std::string& name, std::shared_ptr<BehaviorBase> behaviorBase)
{
    behaviors.insert_or_assign(name, behaviorBase);
}

std::shared_ptr<BehaviorBase> EntityBehaviors::get(const std::string& name) const
{
    return behaviors.at(name);
}

void EntityBehaviors::frame(Entity& entity, FrameTime frameTime)
{
    std::ranges::for_each(behaviors, [&](auto b) { b.second->frame(entity, frameTime); });
}
