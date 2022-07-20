#include "GotoController.h"

#include <Entity.h>
#include <MathHelpers.h>
#include <OsgMathExtensions.h>

using namespace entities;


void GotoController::frame(Entity& entity, FrameTime frameTime)
{
    if (1 == frameTime.frame)
    {
        pidController.setMaxValue(common::makeVec(entity.getProperty<double>("physics.limits.acceleration")));
        pidController.setMinValue(-common::makeVec(entity.getProperty<double>("physics.limits.acceleration")));
    }
    // TODO: acceleration along direction
    //  project pid results along current frame
    auto targetDir = osgext::normalized(entity.getTarget() - entity.getPosition());
    auto ownDir    = osgext::normalized(entity.getAttitude() * osg::Vec3d(0, 0, 1));

    auto calcAcceleration = pidController.calculate(entity.getTarget(), entity.getPosition(), frameTime.delta);
    auto magnitude        = calcAcceleration.length();


    entity.getVelocity() = osgext::normalized(ownDir) * magnitude * 100.0; //    *(ownDir * targetDir) * 0.001;
    // entity.getVelocity() = osg::Vec3d(0.01, 0, 0);
    //     osgext::normalized(ownDir) * magnitude * 100.0; //    *(ownDir * targetDir) * 0.001;

    // experimental: gizmo update
    const auto& gizmos = entity.getGizmos();
    if (gizmos.contains("pidError"))
    {
        const auto& gizmo = gizmos.at("pidError");
        auto        pat   = gizmo.pat;
        pat->setScale(pidController.getPreError());
    }
    if (gizmos.contains("pidValue"))
    {
        const auto& gizmo = gizmos.at("pidValue");
        auto        pat   = gizmo.pat;
        pat->setScale(pidController.getPreError());
    }
}


GotoController::GotoController(const nsConfig::BehaviorConf& conf)
    : BehaviorBase(conf)
{
    const auto& pid = conf.conf["pid"];
    pidController.setPid(osg::Vec3d(pid[0], pid[1], pid[2]));
}
