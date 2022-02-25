#include "PositionController.h"
#include <Entity.h>

using namespace entities;

void PositionController::frame(Entity& entity, FrameTime frameTime)
{
    entity.getAcceleration() = pidController.calculate(entity.getTarget(), entity.getPosition(), frameTime.delta);
}

std::shared_ptr<StateFullBehavior> PositionController::clone(const entities::BehaviorConf& conf)
{
    return std::make_shared<PositionController>(conf.conf);
}

PositionController::PositionController(const Config& conf)
    : StateFullBehavior("position")
{
    const auto& pid = conf["pid"];
    pidController.setPid(osg::Vec3d(pid[0], pid[1], pid[2]));
}

PositionController::PositionController()
    : StateFullBehavior("position")
{
}

