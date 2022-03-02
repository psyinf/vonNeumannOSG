#pragma once
#include <FactoryRegistry.h>
#include <EntityBehavior.h>

#include <memory>
#include <string_view>
#include <boost/function.hpp>
#include <map>


namespace entities
{

class Entities;
class BehaviorBase;
class BehaviorConf;


using BehaviorBaseCtor = boost::function<BehaviorBase*(const Config& conf)>;
class EntityBehaviorRegistry : public common::FactoryRegistry<BehaviorBaseCtor>
{
public:
    std::shared_ptr<BehaviorBase> get(const std::string& entity_type, const entities::BehaviorConf& conf);
    /**
     * add prototype of behavior
     */

    //void add(const std::string& entity_type, std::shared_ptr<BehaviorBase> behavior);
    //void add(std::shared_ptr<BehaviorBase> behavior);

protected:
    std::map<std::string, std::shared_ptr<BehaviorBase>, std::less<>> registry;
};

} // namespace entities