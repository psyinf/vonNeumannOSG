#include "EntityUpdateCallback.h"
#include "Entity.h"


void EntityUpdateCallback::operator()(osg::Node* node, osg::NodeVisitor* nv)
{
	if (lastFrame.getFrameNumber() == 0) {
		lastFrame = *nv->getFrameStamp();
		return;
	}
	nsEntities::Entity* entity = dynamic_cast<nsEntities::Entity*>(node);
	
	if (entity)
	{
		float time_passed_sec =  nv->getFrameStamp()->getSimulationTime()-  lastFrame.getSimulationTime() ;
		//std::cout << time_passed_sec << std::endl;
		
		entity->update(nv->getFrameStamp()->getFrameNumber(), time_passed_sec);
		
		lastFrame = *nv->getFrameStamp();
	}
	traverse(node, nv);
}
