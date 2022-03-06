#pragma once
#include "EntityConf.h"
#include "EntityUpdateCallback.h"
#include "JsonConfigCache.h"

#include <osg/PositionAttitudeTransform>
#include <osg/Vec3d>
#include <osgDB/ReadFile>


namespace entities
{
class BehaviorBase;
class EntityBehaviors;
class EntityManager;

class Entity : public osg::PositionAttitudeTransform
{
    using PropertyName = std::string;

public:
    Entity()  = default;
    ~Entity() = default;

    Entity(const std::string& name, const std::string& config, std::shared_ptr<EntityManager> em);


    const osg::Vec3d& getVelocity() const;
    osg::Vec3d&       getVelocity();
    void              setVelocity(const osg::Vec3d& val);

    const osg::Vec3d& getAcceleration() const;
    osg::Vec3d&       getAcceleration();
    void              setAcceleration(const osg::Vec3d& val);

    const osg::Vec3d& getTarget() const;
    osg::Vec3d&       getTarget();
    void              setTarget(const osg::Vec3d& val);


    virtual void update(int frameNum, float delta_sec);

    virtual void kinematicUpdate(float delta_sec);

    std::shared_ptr<BehaviorBase> getBehavior(const std::string& name) const;

    void addBehavior(const std::string& name, std::shared_ptr<BehaviorBase> behavior);

    template <class T>
    T getProperty(const std::string& key);

    void processProperties(nlohmann::json& json);

private:
    osg::Vec3d target;
    osg::Vec3d velocity;
    osg::Vec3d acceleration;

    std::unique_ptr<EntityBehaviors>                 entityBehaviors = std::make_unique<EntityBehaviors>();
    std::unordered_map<PropertyName, nlohmann::json> entityProperties;
    std::shared_ptr<entities::EntityManager>         entityManager;
};

template <class T>
T entities::Entity::getProperty(const std::string& key)
{
    auto json_value = entityProperties.at(key);
    return json_value.get<T>();
}

} // namespace entities