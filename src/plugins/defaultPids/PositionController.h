#pragma once
#include "EntityBehavior.h"

class PositionController : public entities::StateFullBehavior
{
public:
    explicit PositionController(const entities::Config& conf);

    PositionController();

    void                               frame(entities::Entity& entity, entities::FrameTime frameTime) override;
    std::shared_ptr<StateFullBehavior> clone(const entities::BehaviorConf& conf) override;

    Vec3dPid pidController = Vec3dPid(osg::Vec3d(0.1, 0.0001, 0.01), osg::Vec3d(0.1, 0.1, 0.1));
};
