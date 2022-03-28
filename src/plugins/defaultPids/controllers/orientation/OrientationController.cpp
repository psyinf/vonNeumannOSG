#include "OrientationController.h"

#include <osg/Math>

#include <Entity.h>
#include <MathHelpers.h>
#include <OsgMathExtensions.h>

using namespace entities;


void OrientationController::frame(Entity& entity, FrameTime frameTime)
{
    if (1 == frameTime.frame)
    {
        // pidController.setMaxValue(common::makeVec(entity.getProperty<double>("physics.limits.rotation")));
        // pidController.setMinValue(-common::makeVec(entity.getProperty<double>("physics.limits.rotation")));
        return;
    }

    const auto& targetPos = entity.getTarget();

    auto targetDir = targetPos - entity.getPosition();
    auto length    = targetDir.normalize();

    if (length >= 1.0)
    {
        osg::Quat targetRot;

        targetRot.makeRotate(osg::Vec3d(0, 0, -1), targetDir);


        osg::Quat currentRot = entity.getAttitude();

        auto correction = pidController.calculate(targetRot, currentRot, frameTime.delta);
        entity.setAttitude(entity.getAttitude() * correction);
    }
}


OrientationController::OrientationController(const nsConfig::BehaviorConf& conf)
    : BehaviorBase(conf)
{
    const auto& pid = conf.conf["pid"];
    pidController.setPid(osg::Vec3d(pid[0], pid[1], pid[2]));
}