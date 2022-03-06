#include "Entity.h"

#include "EntityBehaviorRegistry.h"
#include "EntityBehaviors.h"

#include <EntityManager.h>

using namespace entities;

Entity::Entity(const std::string& name, const std::string& config, const std::shared_ptr<EntityManager> em)
    : PositionAttitudeTransform()
    , entityManager(em)
{
    auto conf = nsConfig::load<EntityConf>(config);
    PositionAttitudeTransform::setName(name);
    PositionAttitudeTransform::addChild(osgDB::readNodeFiles(conf.models));
    processProperties(conf.properties);
    for (const auto& behaviorConf : conf.behaviors)
    {
        if (!behaviorConf.enabled)
        {
            continue;
        }
        try
        {
            auto behavior = entityManager->getBehaviorRegistry().get(conf.type, behaviorConf);

            entityBehaviors->add(behaviorConf.type, behavior);

            entityBehaviors->frame(*this, {1, 2});
        }
        catch (const std::exception& e)
        {
            std::cerr << "Cannot add behavior to entity: '" << behaviorConf.type << "'. " << e.what() << std::endl;
        }
    }

    addUpdateCallback(new EntityUpdateCallback());
    // test configuration
    if (getProperty<std::string>("faction") == "red")
    {
        // std::cout << getProperty<std::string>("faction");
    }
}

osg::Vec3d& Entity::getVelocity()
{
    return velocity;
}

const osg::Vec3d& Entity::getVelocity() const
{
    return velocity;
}

void Entity::setVelocity(const osg::Vec3d& val)
{
    velocity = val;
}

osg::Vec3d& Entity::getAcceleration()
{
    return acceleration;
}

const osg::Vec3d& Entity::getAcceleration() const
{
    return acceleration;
}

void Entity::setAcceleration(const osg::Vec3d& val)
{
    acceleration = val;
}

osg::Vec3d& Entity::getTarget()
{
    return target;
}

const osg::Vec3d& Entity::getTarget() const
{
    return target;
}

void Entity::setTarget(const osg::Vec3d& val)
{
    target = val;
}

void Entity::update(int frameNum, float delta_sec)
{
    entityBehaviors->frame(*this, {frameNum, delta_sec});
    kinematicUpdate(delta_sec);
}

void Entity::kinematicUpdate(float delta_sec)
{
    getVelocity() += getAcceleration();
    setPosition(getPosition() + getVelocity() * delta_sec);

    // TODO: turn-rate and acceleration along axis
    osg::Vec3d unitVelocity = velocity;
    unitVelocity.normalize();
    osg::Quat rot;
    rot.makeRotate(osg::Vec3d(0, 0, 1), unitVelocity);
    setAttitude(rot);
}

std::shared_ptr<BehaviorBase> Entity::getBehavior(const std::string& name) const
{
    return entityBehaviors->get(name);
}
void Entity::addBehavior(const std::string& name, std::shared_ptr<BehaviorBase> behavior)
{
    entityBehaviors->add(name, behavior);
}

void Entity::processProperties(nlohmann::json& json)
{
    for (auto iter = json.begin(); iter != json.end(); ++iter)
    {
        entityProperties.try_emplace(iter.key(), iter.value());
    }
}
