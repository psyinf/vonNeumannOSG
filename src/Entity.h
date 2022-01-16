#pragma once
#include "osg/Vec3d"
#include "osg/PositionAttitudeTransform"
#include "EntityUpdateCallback.h"
#include "EntityBehavior.h"
#include "EntityConf.h"
#include "ConfigCache.h"
#include <osgDB/ReadFile>
namespace nsEntities {

class Entity : public osg::PositionAttitudeTransform {
public:
	Entity() = default;
	~Entity() = default;
	
	Entity(const std::string& config) {
		auto conf = nsConfig::load<EntityConf>(config);
		addChild(osgDB::readNodeFiles(conf.models));
		for (const auto& behavior : conf.behaviors) {
			try {
				entityBehavior.add(BehaviorRegistry::get(behavior));
			}
			catch (const std::exception& e) {
				std::cerr << "Cannot add behavior: '" << behavior << "'. Not found" << std::endl;
			}
		}
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
	// reflect entities 'kinematically' (invert velocity)
	nsEntities::EntityBehavior entityBehavior;
	
};

}//namespace