#pragma once

#include "EntityConf.h"
#include "Vec3dPid.h"

#include <osg/BoundingBox>

#include <nlohmann/json_fwd.hpp>
#include <iostream>

class SceneConfig;
namespace entities {
class Entity;

using FrameTime = struct { int frame; float delta; };
using Config = nlohmann::json;
/*
 * Some default entity behaviors as functions
 */
class BehaviorBase  {
public:
	explicit BehaviorBase(const std::string& name)
		:name(name){
	};
	explicit BehaviorBase(std::string&& name) 
        :name(std::move(name)){
	}
	const std::string& getName() const {
		return name;
	}

	const std::string name;
	virtual void frame(Entity& entity, FrameTime frameTime) = 0;
    virtual void      setConfiguration(const Config& conf){ 
		//optional handling 
	};
};

/* Subclass that describes a behavior with own state. A PID controller relying on the previous frame e.g.*/
class StateFullBehavior : public BehaviorBase {
public:
	using BehaviorBase::BehaviorBase;
	virtual std::shared_ptr<StateFullBehavior> clone(const entities::BehaviorConf& conf) = 0;
};

class Reflector : public BehaviorBase {
public:
	explicit Reflector(const Config& conf);
	osg::BoundingBox box;
	void frame(Entity& entity, FrameTime frameTime) override;
};

class Torusifator : public BehaviorBase {
public:
	explicit Torusifator(const Config& conf);
	osg::BoundingBox box;
	void frame(Entity& entity, FrameTime frameTime) override;
};

class PositionController : public StateFullBehavior {
public:
	explicit PositionController(const Config& conf);

	PositionController()
	: StateFullBehavior("position"){

	}

	void frame(Entity& entity, FrameTime frameTime) override;
	std::shared_ptr<StateFullBehavior> clone(const entities::BehaviorConf& conf) override;

	Vec3dPid pidController = Vec3dPid(osg::Vec3d(0.1, 0.0001, 0.01), osg::Vec3d(0.1, 0.1, 0.1));
};

class BehaviorRegistry {
public:
	static std::shared_ptr<BehaviorBase> get(const std::string& entity_type, const entities::BehaviorConf& conf) {
	
		std::shared_ptr<BehaviorBase> instance;
		if (registry.contains(entity_type + "_" + conf.type)) {
			instance = registry.at(entity_type + "_" + conf.type);
			//TODO: we need to cache setting up conf 
			instance->setConfiguration(conf.conf);
		}
		else {
			instance = registry.at(conf.type);
		}
		
		auto stateful_instance = std::dynamic_pointer_cast<StateFullBehavior>(instance);
		if (stateful_instance) {
			return stateful_instance->clone(conf);
		}
		else {
			return instance;
		}
	}
	/**
	 * add prototype of behavior
	 */
	static void add(const std::string& entity_type, std::shared_ptr<BehaviorBase> behavior) {
		std::cout << "adding behavior: " << behavior->getName() << " for entity type " << entity_type  << " to registry" << std::endl;
		registry.insert_or_assign(entity_type + "_" + behavior->getName(), behavior);
		
	}
	static void add(std::shared_ptr<BehaviorBase> behavior) {
		std::cout << "adding generic behavior: " << behavior->getName() << " to registry" << std::endl;
		registry.insert_or_assign(behavior->getName(), behavior);
	}
protected:
	inline static std::map<std::string, std::shared_ptr<BehaviorBase>> registry;
};

class EntityBehavior {
public:
	void add(std::shared_ptr<entities::BehaviorBase> behaviorBase) {
		behaviors.push_back(behaviorBase);
	}

	std::shared_ptr<BehaviorBase> get(const std::string& name) const {
		auto res = std::find_if(std::cbegin(behaviors), std::cend(behaviors), [&name](const auto& b) {return b->getName() == name; });
		return (*res);
	}

	virtual void frame(Entity& entity, FrameTime frameTime);
private:
	std::vector<std::shared_ptr<BehaviorBase>>	behaviors;
};

} //namespace