#pragma once
#include <EntityBehavior.h>

namespace entities
{
class Reflector : public BehaviorBase
{
    osg::BoundingBox box;

public:
    explicit Reflector(const config::BehaviorConf& conf);
    void frame(Entity& entity, FrameTime frameTime) override;
};

class Torusifator : public BehaviorBase
{
    osg::BoundingBox box;

public:
    explicit Torusifator(const config::BehaviorConf& conf);
    void frame(Entity& entity, FrameTime frameTime) override;
};


} // namespace entities
