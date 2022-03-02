#include "PositionController.h"
#include <Entity.h>

using namespace entities;

void PositionController::frame(Entity& entity, FrameTime frameTime)
{
    entity.getAcceleration() = pidController.calculate(entity.getTarget(), entity.getPosition(), frameTime.delta);
}


PositionController::PositionController(const BehaviorConf& conf)
    : BehaviorBase(conf)
{
    const auto& pid = conf.conf["pid"];
    pidController.setPid(osg::Vec3d(pid[0], pid[1], pid[2]));
}


