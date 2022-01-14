#pragma once
#include "osg/Vec3d"
#include "osg/PositionAttitudeTransform"
#include "EntityUpdateCallback.h"
#include "EntityCache.h"
#include "EntityBehavior.h"

namespace nsEntities {

class Entity : public osg::PositionAttitudeTransform {
public:
	Entity() = default;
	~Entity() = default;
	
	Entity(const std::string& model) {
		addChild(EntityCache::readNodeFile(model));
		//addChild(EntityCache::readNodeFile("data/axes.osgt"));
		addUpdateCallback(new EntityUpdateCallback());
	}



	const osg::Vec3d& getVelocity() const { return velocity; }
	osg::Vec3d& getVelocity() {	return velocity; }
	void setVelocity(osg::Vec3d val) { velocity = val; }
	

	virtual void update(float delta_sec) {
	
		kinematicUpdate(delta_sec);
		entityBehavior.frame(*this, delta_sec);

	}

	virtual void kinematicUpdate(float delta_sec)
	{
		setPosition(getPosition() + getVelocity() * delta_sec);

		osg::Vec3d unitVelocity = velocity;
		unitVelocity.normalize();
		osg::Quat rot; rot.makeRotate(osg::Vec3d(0, 0, 1), unitVelocity );
		setAttitude(rot);

	}
	
protected:
	osg::Vec3d velocity;
	nsEntities::EntityBehavior entityBehavior;
	
};

}//namespace