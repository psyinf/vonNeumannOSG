#pragma once


#include <osg/BoundingBox>
#include "Vec3dPid.h"
class SceneConfig;
namespace nsEntities {
class Entity;
/*
 * Some default entity behaviors as functions
 */


class EntityBehavior {
public:

	//IDEA: map functions by name and define a simple behavior by defining the order/subset of the behavioral functions "externally"
	virtual void frame(Entity& entity, float frame_time);
protected:
	// reflect entities 'kinematically' (invert velocity)
	virtual void reflectInsideBox(Entity& entity, const osg::BoundingBox& box);

	Vec3dPid pidController = Vec3dPid(osg::Vec3d(0.01,0.0001,0.01), osg::Vec3d(0.1,0.1,0.1));
};

} //namespace