#pragma once
#include <boost/function.hpp>

#include <EntityBehavior.h>
#include <FactoryRegistry.h>
#include <map>
#include <memory>
#include <string_view>


namespace entities
{

class Entities;
class BehaviorBase;
class BehaviorConf;


using BehaviorBaseCtor = boost::function<BehaviorBase*(const Config& conf)>;
class EntityBehaviorRegistry : public common::FactoryRegistry<BehaviorBaseCtor>
{
public:
    std::shared_ptr<BehaviorBase> get(const std::string& entity_type, const nsConfig::BehaviorConf& conf);

protected:
    std::map<std::string, std::shared_ptr<BehaviorBase>, std::less<>> registry;
};

} // namespace entities