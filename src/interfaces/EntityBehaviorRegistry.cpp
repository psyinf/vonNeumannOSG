#include "EntityBehaviorRegistry.h"
#include "EntityConf.h"
#include "EntityBehavior.h"

#include <iostream>

using namespace entities;

std::shared_ptr<BehaviorBase>
EntityBehaviorRegistry::get(const std::string& entity_type, const BehaviorConf& conf)
{
    auto ctor = getPrototype(conf.type);
    return std::unique_ptr<BehaviorBase>(ctor(conf));
 //   return std::make_shared<BehaviorBase>(getPrototype(entity_type)(conf));
    /* --
    std::shared_ptr<BehaviorBase> instance;
    if (registry.contains(entity_type + "_" + conf.type))
    {
        instance = registry.at(entity_type + "_" + conf.type);
        // TODO: we need to cache setting up conf
        instance->setConfiguration(conf.conf);
    }
    else
    {
        instance = registry.at(conf.type);
    }

    auto stateful_instance = std::dynamic_pointer_cast<StateFullBehavior>(instance);
    if (stateful_instance)
    {
        return stateful_instance->clone(conf);
    }
    else
    {
        return instance;
    }

    */
}
/*
void entities::EntityBehaviorRegistry::add(std::shared_ptr<BehaviorBase> behavior)
{
   // std::cout << "adding generic behavior: " << behavior->getName() << " to registry" << std::endl;
    registry.insert_or_assign(behavior->getName(), behavior);
}

void entities::EntityBehaviorRegistry::add(const std::string& entity_type, std::shared_ptr<BehaviorBase> behavior)
{
    std::cout << "adding behavior: " << behavior->getName() << " for entity type " << entity_type << " to registry" << std::endl;
    registry.insert_or_assign(entity_type + "_" + behavior->getName(), behavior);
}
*/