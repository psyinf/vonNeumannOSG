#pragma once
#include "EntityBehavior.h"
#include "QuatPid.h"


class OrientationController : public entities::BehaviorBase
{
public:
    explicit OrientationController(const nsConfig::BehaviorConf& conf);

    ~OrientationController() = default;

    void frame(entities::Entity& entity, entities::FrameTime frameTime) override;

    QuatPid pidController = QuatPid(osg::Vec3d(0.1, 0.0001, 0.01), osg::Vec3d(0.1, 0.1, 0.1));
};