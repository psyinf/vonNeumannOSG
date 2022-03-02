#pragma once
#include "EntityBehavior.h"

class PositionController : public entities::BehaviorBase
{
public:
    explicit PositionController(const entities::BehaviorConf& conf);

    ~PositionController() {
        std::cout << "kaputt";
    }

    void                               frame(entities::Entity& entity, entities::FrameTime frameTime) override;

    Vec3dPid pidController = Vec3dPid(osg::Vec3d(0.1, 0.0001, 0.01), osg::Vec3d(0.1, 0.1, 0.1));
};
