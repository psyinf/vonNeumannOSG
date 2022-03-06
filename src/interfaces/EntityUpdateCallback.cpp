#include "EntityUpdateCallback.h"

#include "Entity.h"


void EntityUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
    if (lastFrame.getFrameNumber() == 0)
    {
        lastFrame = *nv->getFrameStamp();
        return;
    }
    auto* entity = dynamic_cast<entities::Entity*>(node);

    if (entity)
    {
        float time_passed_sec = nv->getFrameStamp()->getSimulationTime() - lastFrame.getSimulationTime();

        entity->update(nv->getFrameStamp()->getFrameNumber(), time_passed_sec);

        lastFrame = *nv->getFrameStamp();
    }
    else
    {
        std::cerr << "EntityUpdateCallback registered to non-entity type" << std::endl;
    }
    traverse(node, nv);
}
