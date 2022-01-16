#pragma once


#include <osg/BoundingBox>
#include "Vec3dPid.h"
#include <nlohmann/json_fwd.hpp>

class SceneConfig;
namespace nsEntities {
class Entity;

using FrameTime = float;
using Config = nlohmann::json;
/*
 * Some default entity behaviors as functions
 */
class BehaviorBase {
public:
	BehaviorBase(const std::string& name, const Config& conf )
		:name(name){
	};
	const std::string& getName() const {
		return name;
	}
	const std::string& name;
	virtual void frame(Entity& entity, FrameTime frameTime) = 0;
};

class Reflector : public BehaviorBase {
public:
	Reflector(const Config& conf);
	osg::BoundingBox box;
	virtual void frame(Entity& entity, FrameTime frameTime) override;
};

class PositionController : public BehaviorBase {
public:
	PositionController(const Config& conf)
		:BehaviorBase("positionController", conf) {
	}

	virtual void frame(Entity& entity, FrameTime frameTime) override;

	Vec3dPid pidController = Vec3dPid(osg::Vec3d(0.01, 0.0001, 0.01), osg::Vec3d(0.1, 0.1, 0.1));

};


class BehaviorRegistry {
public:
	std::shared_ptr<BehaviorBase> get(const std::string& name) {
		return registry.at(name);
	}
	void add(std::shared_ptr<BehaviorBase> behavior) {
		registry.emplace(behavior->getName(), behavior);
	}
protected:
	std::map<std::string, std::shared_ptr<BehaviorBase>> registry;
};

class EntityBehavior {
public:
	void add(std::shared_ptr<BehaviorBase> behaviorBase) {
		behaviors.emplace_back(behaviorBase);
	}

	virtual void frame(Entity& entity, FrameTime frameTime);
protected:
	std::vector<std::shared_ptr<BehaviorBase>>	behaviors;
};

} //namespace