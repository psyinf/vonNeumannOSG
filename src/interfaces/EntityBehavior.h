#pragma once

#include "Entity.h"
#include "EntityConf.h"
#include "FrameTime.h"
#include <osg/BoundingBox>

#include <BehaviorConf.h>
#include <iostream>
#include <nlohmann/json_fwd.hpp>

class SceneConfig;


namespace entities
{
class Entity;
class Entities;


using Config = nlohmann::json;
/*
 * Some default entity behaviors as functions
 */
class BehaviorBase
{
public:
    explicit BehaviorBase(const config::BehaviorConf& conf)
        : conf(conf){};

    virtual void                  frame(Entity& entity, FrameTime frameTime) = 0;
    const config::BehaviorConf& getConf() const
    {
        return conf;
    }

private:
    config::BehaviorConf conf;
};


} // namespace entities