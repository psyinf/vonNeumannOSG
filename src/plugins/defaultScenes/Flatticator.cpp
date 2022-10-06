#include "Flatticator.h"

#include <AxisJson.h>

using namespace entities;

Flatticator::Flatticator(const config::BehaviorConf& conf)
    : BehaviorBase(conf)
{
    this->flattenAxis = conf.conf["axis"];
}

void Flatticator::frame(Entity& entity, FrameTime frameTime)
{
    auto flattenVec = osg::Matrixd();
    switch (flattenAxis)
    {
    case Axis::X:
        flattenVec(0, 0) = 0.0;
        break;
    case Axis::Y:
        flattenVec(1, 1) = 0.0;
        break;
    case Axis::Z:
        flattenVec(2, 2) = 0.0;
        break;
    }

    entity.setAcceleration(flattenVec * entity.getAcceleration());
    entity.setPosition(flattenVec * entity.getPosition());
    entity.setVelocity(flattenVec * entity.getVelocity());
    // TODO: modify attitude
}
