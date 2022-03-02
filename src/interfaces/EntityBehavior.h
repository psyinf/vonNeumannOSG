#pragma once

#include "EntityConf.h"
#include "Entity.h"
#include "Vec3dPid.h"

#include <osg/BoundingBox>

#include <nlohmann/json_fwd.hpp>
#include <iostream>

class SceneConfig;


namespace entities {
class Entity;
class Entities;

using FrameTime = struct { int frame; float delta; };
using Config = nlohmann::json;
/*
 * Some default entity behaviors as functions
 */
class BehaviorBase  {
public:
    explicit BehaviorBase(const BehaviorConf& conf){};
	
    virtual void      frame(Entity& entity, FrameTime frameTime){};
};


class Reflector : public BehaviorBase {
public:
    explicit Reflector(const BehaviorConf& conf);
	osg::BoundingBox box;
	void frame(Entity& entity, FrameTime frameTime) override;
};

class Torusifator : public BehaviorBase {
public:
    explicit Torusifator(const BehaviorConf& conf);
	osg::BoundingBox box;
	void frame(Entity& entity, FrameTime frameTime) override;
};


} //namespace