#include "PositionController.h"

#include <Entity.h>

using namespace entities;

void PositionController::frame(Entity& entity, FrameTime frameTime)
{
    if (0 == frameTime.frame)
    {
        // configure
        // entity.getProperty("physics/limits/acceleration");
    }
    entity.getAcceleration() = pidController.calculate(entity.getTarget(), entity.getPosition(), frameTime.delta);
}


PositionController::PositionController(const nsConfig::BehaviorConf& conf)
    : BehaviorBase(conf)
{
    const auto& pid = conf.conf["pid"];
    pidController.setPid(osg::Vec3d(pid[0], pid[1], pid[2]));
}
