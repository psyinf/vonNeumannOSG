#pragma once
#include <osg/Vec3d>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include "EntityUpdateCallback.h"
#include "EntityBehavior.h"
#include "EntityConf.h"
#include "JsonConfigCache.h"


namespace entities {

class Entity : public osg::PositionAttitudeTransform {
	using Property = std::string;
public:
	Entity() = default;
	~Entity() = default;
	
	Entity(const std::string& name, const std::string& config);



	const osg::Vec3d& getVelocity() const;
	osg::Vec3d& getVelocity();
	void setVelocity(const osg::Vec3d& val);

	const osg::Vec3d& getAcceleration() const;
	osg::Vec3d& getAcceleration();
	void setAcceleration(const osg::Vec3d& val);

	const osg::Vec3d& getTarget() const;
	osg::Vec3d& getTarget(); 
	void setTarget(const osg::Vec3d& val);


	virtual void update(int frameNum, float delta_sec);

	virtual void kinematicUpdate(float delta_sec);

	std::shared_ptr<BehaviorBase> getBehavior(const std::string& name) const;
	
	template <class T> 
	T getProperty(const std::string& key);

	void processProperties(nlohmann::json& json);

private:
	osg::Vec3d target;
	osg::Vec3d velocity;
	osg::Vec3d acceleration;
	// reflect entities 'kinematically' (invert velocity)
	entities::EntityBehavior entityBehaviors;
    std::unordered_map<Property, Config> entityProperties;
	


};

template <class T>
T entities::Entity::getProperty(const std::string& key)
{
    auto json_value = entityProperties.at(key);
    return json_value.get<T>();
}

}//namespace