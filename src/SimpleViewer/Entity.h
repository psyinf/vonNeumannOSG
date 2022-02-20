#pragma once
#include "osg/Vec3d"
#include "osg/PositionAttitudeTransform"
#include "EntityUpdateCallback.h"
#include "EntityBehavior.h"
#include "EntityConf.h"
#include "JsonConfigCache.h"
#include <osgDB/ReadFile>

namespace nsEntities {

class Entity : public osg::PositionAttitudeTransform {
public:
	Entity() = default;
	~Entity() = default;
	
	Entity(const std::string& name, const std::string& config) {
		auto conf = nsConfig::load<EntityConf>(config);
		setName(name);
		addChild(osgDB::readNodeFiles(conf.models));
		for (const auto& behaviorConf : conf.behaviors) {
			try {
				auto behavior = BehaviorRegistry::get(conf.type, behaviorConf);
				
				entityBehaviors.add(behavior);
			}
			catch (const std::exception& e) {
				std::cerr << "Cannot add behavior: '" << behaviorConf.type << "'. Not found" << std::endl;
			}
		}
		addUpdateCallback(new EntityUpdateCallback());
	}



	const osg::Vec3d& getVelocity() const { return velocity; }
	osg::Vec3d& getVelocity() {	return velocity; }
	void setVelocity(const osg::Vec3d& val) { velocity = val; }

	const osg::Vec3d& getAcceleration() const { return acceleration; }
	osg::Vec3d& getAcceleration() { return acceleration; }
	void setAcceleration(const osg::Vec3d& val) { acceleration = val; }

	const osg::Vec3d& getTarget() const { return target; }
	osg::Vec3d& getTarget() { return target; } 
	void setTarget(const osg::Vec3d& val) { target = val; }


	virtual void update(int frameNum, float delta_sec) {
		entityBehaviors.frame(*this, {frameNum, delta_sec});
		kinematicUpdate(delta_sec);
	}

	virtual void kinematicUpdate(float delta_sec)
	{
		getVelocity() += getAcceleration() ;
		setPosition(getPosition() + getVelocity() * delta_sec);

		//TODO: turn-rate and acceleration along axis
		osg::Vec3d unitVelocity = velocity;
		unitVelocity.normalize();
		osg::Quat rot; rot.makeRotate(osg::Vec3d(0, 0, 1), unitVelocity );
		setAttitude(rot);
	}

	std::shared_ptr<BehaviorBase> getBehavior(const std::string& name) const {
		return entityBehaviors.get(name);
	}
	
private:
	osg::Vec3d target;
	osg::Vec3d velocity;
	osg::Vec3d acceleration;
	// reflect entities 'kinematically' (invert velocity)
	nsEntities::EntityBehavior entityBehaviors;
	
};

}//namespace