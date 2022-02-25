#include "Entity.h"



 entities::Entity::Entity(const std::string& name, const std::string& config)
    : PositionAttitudeTransform()
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
            auto behavior = BehaviorRegistry::get(conf.type, behaviorConf);

            entityBehaviors.add(behavior);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Cannot add behavior: '" << behaviorConf.type << "'. Not found" << std::endl;
        }
    }
   
    addUpdateCallback(new EntityUpdateCallback());
    //test configuration
    if (getProperty<std::string>("faction") == "red")
    {
        std::cout << getProperty<std::string>("faction");
    }
}

osg::Vec3d& entities::Entity::getVelocity()
{
    return velocity;
}

const osg::Vec3d& entities::Entity::getVelocity() const
{
    return velocity;
}

void entities::Entity::setVelocity(const osg::Vec3d& val)
{
    velocity = val;
}

osg::Vec3d& entities::Entity::getAcceleration()
{
    return acceleration;
}

const osg::Vec3d& entities::Entity::getAcceleration() const
{
    return acceleration;
}

void entities::Entity::setAcceleration(const osg::Vec3d& val)
{
    acceleration = val;
}

osg::Vec3d& entities::Entity::getTarget()
{
    return target;
}

const osg::Vec3d& entities::Entity::getTarget() const
{
    return target;
}

void entities::Entity::setTarget(const osg::Vec3d& val)
{
    target = val;
}

void entities::Entity::update(int frameNum, float delta_sec)
{
    entityBehaviors.frame(*this, {frameNum, delta_sec});
    kinematicUpdate(delta_sec);
}

void entities::Entity::kinematicUpdate(float delta_sec)
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

std::shared_ptr<entities::BehaviorBase> entities::Entity::getBehavior(const std::string& name) const
{
    return entityBehaviors.get(name);
}

void entities::Entity::processProperties(nlohmann::json& json)
{
    for (auto iter = json.begin(); iter != json.end(); ++iter)
    {
        entityProperties.try_emplace(iter.key(), iter.value());
    }
}
