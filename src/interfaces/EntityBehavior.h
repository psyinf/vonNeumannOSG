#pragma once

#include "Entity.h"
#include "EntityConf.h"

#include <osg/BoundingBox>

#include <BehaviorConf.h>
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
    explicit BehaviorBase(const nsConfig::BehaviorConf& conf)
        : conf(conf){};

    virtual void                  frame(Entity& entity, FrameTime frameTime) = 0;
    const nsConfig::BehaviorConf& getConf() const
    {
        return conf;
    }

private:
    nsConfig::BehaviorConf conf;
};


} // namespace entities