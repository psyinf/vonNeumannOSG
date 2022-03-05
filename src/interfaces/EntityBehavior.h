#pragma once

#include "Entity.h"
#include "EntityConf.h"

#include <osg/BoundingBox>

#include <iostream>
#include <nlohmann/json_fwd.hpp>

class SceneConfig;


namespace entities
{
class Entity;
class Entities;

using FrameTime = struct
{
    int   frame;
    float delta;
};
using Config = nlohmann::json;
/*
 * Some default entity behaviors as functions
 */
class BehaviorBase
{
public:
    explicit BehaviorBase(const BehaviorConf& conf){};

    virtual void frame(Entity& entity, FrameTime frameTime) = 0;
};


} // namespace entities