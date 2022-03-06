#include "SimpleScene.h"

#include "Entity.h"
#include "EntityBehavior.h"
#include "EntityBehaviorRegistry.h"
#include "EntityManager.h"
#include "SceneConfig.h"

#include <JsonConfigCache.h>

#include <random>


void SimpleScene::load(const std::string& fileName)
{
    std::shared_ptr<entities::EntityManager> entityManager = std::make_unique<entities::EntityManager>();
    const auto                               scene         = nsConfig::load<nsConfig::SceneConfig>(fileName);

    // load behaviors from config
    std::vector<std::pair<std::string, std::shared_ptr<entities::BehaviorBase>>> sceneBehaviorInstances;
    for (auto scene_behavior : scene.sceneBehaviors)
    {
        auto instance = entityManager->getBehaviorRegistry().get(scene_behavior.type, scene_behavior);
        sceneBehaviorInstances.emplace_back(std::make_pair(scene_behavior.type, instance));
    }


    std::default_random_engine generator;
    std::normal_distribution   vel_distribution(0.0, 3.0);
    std::normal_distribution   pos_distribution(0.0, 100.0);

    osg::BoundingSphere bounds;
    for (size_t i = scene.numDrones; i-- > 0;)
    {
        osg::ref_ptr<entities::Entity> model = new entities::Entity(std::format("drone{}", i), scene.defaultEntity, entityManager);
        // add global behaviors
        // TODO: add based on configuration of entity
        std::ranges::for_each(sceneBehaviorInstances, [&model](auto inst) { model->addBehavior(inst.first, inst.second); });

        if (bounds.radius() < 0)
        {
            bounds = model->getBound();
        }
        osg::Matrix mat;

        model->setPosition(osg::Vec3d(pos_distribution(generator), pos_distribution(generator), pos_distribution(generator)));
        model->setVelocity(osg::Vec3d(vel_distribution(generator) * bounds.radius(), vel_distribution(generator) * bounds.radius(), vel_distribution(generator) * bounds.radius()));
        root->addChild(model);
    }
}

osg::Group* SimpleScene::getSceneRoot()
{
    return root;
}
