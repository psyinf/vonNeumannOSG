#pragma once
#include "Axis.h"

#include <EntityBehavior.h>
namespace entities
{

class Flatticator : public BehaviorBase
{
    Axis flattenAxis;

public:
    explicit Flatticator(const config::BehaviorConf& conf);
    void frame(Entity& entity, FrameTime frameTime) override;
};
} // namespace entities