#include "Entity.h"

#include "EntityBehaviorRegistry.h"
#include "EntityBehaviors.h"

#include <EntityManager.h>

using namespace entities;

Entity::Entity(const std::string& name, const std::string& config, const std::shared_ptr<EntityManager> em)
    : PositionAttitudeTransform()
    , entityManager(em)
{
    auto conf = nsConfig::load<nsConfig::EntityConf>(config);
    PositionAttitudeTransform::setName(name);

    for (auto& model : conf.models)
    {
        auto pat = new osg::PositionAttitudeTransform;
        pat->addChild(osgDB::readNodeFile(model.model));
        nsConfig::PositionAttitudeConf::from(pat, model.pat);

        PositionAttitudeTransform::addChild(pat);
    }


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
    for (auto& gizmo : conf.gizmos)
    {
        auto model = osgDB::readNodeFile(gizmo.model);
        auto pat   = new osg::PositionAttitudeTransform;
        addChild(pat);

        pat->addChild(model);
        gizmoModelIndices.emplace(gizmo.type, pat);
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
}

std::shared_ptr<BehaviorBase> Entity::getBehavior(const std::string& name) const
{
    return entityBehaviors->get(name);
}
void Entity::addBehavior(const std::string& name, std::shared_ptr<BehaviorBase> behavior)
{
    entityBehaviors->add(name, behavior);
}

void Entity::processProperties(const nlohmann::json& json)
{
    entityProperties = json;
}

void Entity::updateGizmos(osg::NodeVisitor* nv)
{
    for (const auto& gizmo : gizmoModelIndices)
    {
        if (gizmo.first == "velocity")
        {
            auto      pat = reinterpret_cast<osg::PositionAttitudeTransform*>(gizmo.second.get());
            osg::Quat q;
            auto      current = getAttitude();
            q.makeRotate(Entity::forwardDirection, Entity::getVelocity());
            pat->setAttitude(q * current.inverse());
            pat->setScale(osg::Vec3d(10, 10, 25));
        }
    }
}
