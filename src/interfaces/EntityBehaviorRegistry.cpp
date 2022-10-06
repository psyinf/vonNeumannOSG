#include "EntityBehaviorRegistry.h"

#include "EntityBehavior.h"
#include "EntityConf.h"

#include <iostream>
#include <ranges>

using namespace entities;

std::shared_ptr<BehaviorBase>
EntityBehaviorRegistry::get(const std::string& entity_type, const config::BehaviorConf& conf)
{
    auto ctor = getPrototype(conf.type);
    return std::unique_ptr<BehaviorBase>(ctor(conf));
}