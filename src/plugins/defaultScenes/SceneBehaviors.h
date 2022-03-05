#pragma once
#include "Vec3dPid.h"

#include <EntityBehavior.h>

namespace entities
{
class Reflector : public BehaviorBase
{
public:
    explicit Reflector(const BehaviorConf& conf);
    osg::BoundingBox box;
    void             frame(Entity& entity, FrameTime frameTime) override;
};

class Torusifator : public BehaviorBase
{
public:
    explicit Torusifator(const BehaviorConf& conf);
    osg::BoundingBox box;
    void             frame(Entity& entity, FrameTime frameTime) override;
};
} // namespace entities
