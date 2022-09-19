#include "EntityUpdateCallback.h"

#include "Entity.h"
#include "log.h"

void EntityUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    auto* entity = dynamic_cast<entities::Entity*>(node);
    if (!entity)
    {
        LOG(FATAL) << "EntityUpdateCallback registered to non-entity type";
        return;
    }

    if (lastFrame.getFrameNumber() == 0)
    {
        entity->update(nv->getFrameStamp()->getFrameNumber(), std::numeric_limits<float>::min());
        entity->updateGizmos(nv);
        lastFrame = *nv->getFrameStamp();
        return;
    }


    float time_passed_sec = nv->getFrameStamp()->getSimulationTime() - lastFrame.getSimulationTime();
    if (time_passed_sec < std::numeric_limits<float>::min())
    {
        return;
    }

    entity->update(nv->getFrameStamp()->getFrameNumber(), time_passed_sec);

    lastFrame = *nv->getFrameStamp();

    entity->updateGizmos(nv);


    traverse(node, nv);
}
