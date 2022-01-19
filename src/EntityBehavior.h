#pragma once

#include "EntityConf.h"
#include <osg/BoundingBox>
#include "Vec3dPid.h"
#include <nlohmann/json_fwd.hpp>
#include <iostream>

class SceneConfig;
namespace nsEntities {
class Entity;

using FrameTime = float;
using Config = nlohmann::json;
/*
 * Some default entity behaviors as functions
 */
class BehaviorBase  {
public:
	BehaviorBase(const std::string& name)
		:name(name){
	};
	const std::string& getName() const {
		return name;
	}

	const std::string name;
	virtual void frame(Entity& entity, FrameTime frameTime) = 0;
	
};
/* Subclass that describes a behavior with own state. A PID controller relying on the previous frame e.g.*/
class StateFullBehavior : public BehaviorBase {
public:
	StateFullBehavior(const std::string& name)
		:BehaviorBase(name) {
	}
	virtual std::shared_ptr<StateFullBehavior> clone(const nsEntities::BehaviorConf& conf) = 0;
};

class Reflector : public BehaviorBase {
public:
	Reflector(const Config& conf);
	osg::BoundingBox box;
	virtual void frame(Entity& entity, FrameTime frameTime) override;
};

class Torusifator : public BehaviorBase {
public:
	Torusifator(const Config& conf);
	osg::BoundingBox box;
	virtual void frame(Entity& entity, FrameTime frameTime) override;
};

class PositionController : public StateFullBehavior {
public:
	PositionController(const Config& conf);

	PositionController()
	: StateFullBehavior("position"){

	}


	virtual void frame(Entity& entity, FrameTime frameTime) override;

	Vec3dPid pidController = Vec3dPid(osg::Vec3d(0.1, 0.0001, 0.01), osg::Vec3d(0.1, 0.1, 0.1));


	virtual std::shared_ptr<StateFullBehavior> clone(const nsEntities::BehaviorConf& conf) override;

};


class BehaviorRegistry {
public:
	static std::shared_ptr<BehaviorBase> get(const nsEntities::BehaviorConf& conf) {
		auto instance = registry.at(conf.name);
		auto stateful_instance = std::dynamic_pointer_cast<StateFullBehavior>(instance);
		if (stateful_instance) {
			return stateful_instance->clone(conf);
		}
		else {
			return instance;
		}
		
	}
	static void add(std::shared_ptr<BehaviorBase> behavior) {
		std::cout << "adding " << behavior->getName() << " to registry" << std::endl;
		registry.insert_or_assign(behavior->getName(), behavior);
		
	}
protected:
	inline static std::map<std::string, std::shared_ptr<BehaviorBase>> registry;
};

class EntityBehavior {
public:
	void add(std::shared_ptr<nsEntities::BehaviorBase> behaviorBase) {
		behaviors.push_back(behaviorBase);
	}

	virtual void frame(Entity& entity, FrameTime frameTime);
protected:
	std::vector<std::shared_ptr<BehaviorBase>>	behaviors;
};

} //namespace