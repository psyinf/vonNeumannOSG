#include "SimpleScene.h"

#include "Entity.h"
#include "EntityBehavior.h"
#include "EntityBehaviorRegistry.h"
#include "EntityManager.h"
#include "SceneConfig.h"

#include <JsonConfigCache.h>

#include <osgDb/ReadFile>

#include <random>

void SimpleScene::load(const std::string& fileName)
{
    std::shared_ptr<entities::EntityManager> entityManager = std::make_unique<entities::EntityManager>();
    const auto                               scene         = nsConfig::load<nsConfig::SceneConfig>(fileName);

    // load behaviors from config
    std::vector<std::pair<std::string, std::shared_ptr<entities::BehaviorBase>>> sceneBehaviorInstances;
    for (auto& scene_behavior : scene.sceneBehaviors)
    {
        auto instance = entityManager->getBehaviorRegistry().get(scene_behavior.type, scene_behavior);
        sceneBehaviorInstances.emplace_back(std::make_pair(scene_behavior.type, instance));
    }

    for (auto& marker : scene.markers)
    {
        if (!marker.enabled)
        {
            continue;
        }
        auto model = osgDB::readNodeFile(marker.model);
        auto pat   = new osg::PositionAttitudeTransform();

        nsConfig::PositionAttitudeConf::from(pat, marker.pat);

        pat->addChild(model);
        // TODO: re-normalize normals after scale?
        root->addChild(pat);
    }

    // TODO: configurable placers
    std::default_random_engine generator;
    std::normal_distribution   vel_distribution(0.0, 3.0);
    std::normal_distribution   pos_distribution(0.0, 100.0);

    osg::BoundingSphere bounds;
    for (size_t i = scene.numDrones; i-- > 0;)
    {
        osg::ref_ptr<entities::Entity> entity = new entities::Entity(std::format("drone{}", i), scene.defaultEntity, entityManager);
        // add global behaviors
        // TODO: add based on configuration of entity
        std::ranges::for_each(sceneBehaviorInstances, [&entity](auto inst) { entity->addBehavior(inst.first, inst.second); });

        if (bounds.radius() < 0)
        {
            bounds = entity->getBound();
        }
        osg::Matrix mat;

        entity->setPosition(osg::Vec3d(pos_distribution(generator), pos_distribution(generator), pos_distribution(generator)));
        entity->setVelocity(osg::Vec3d(vel_distribution(generator) * bounds.radius(), vel_distribution(generator) * bounds.radius(), vel_distribution(generator) * bounds.radius()));
        root->addChild(entity);

        root->getOrCreateStateSet()->setMode(GL_RESCALE_NORMAL, osg::StateAttribute::ON);
    }
}

osg::Group* SimpleScene::getSceneRoot()
{
    return root;
}
