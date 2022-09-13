#pragma once
#include "EntityBehavior.h"
#include "Vec3dPid.h"


class PositionController : public entities::BehaviorBase
{
public:
    explicit PositionController(const nsConfig::BehaviorConf& conf);

    ~PositionController() = default;

    void frame(entities::Entity& entity, FrameTime frameTime) override;

    Vec3dPid pidController = Vec3dPid(osg::Vec3d(0.1, 0.0001, 0.01), osg::Vec3d(0.1, 0.1, 0.1));
};
