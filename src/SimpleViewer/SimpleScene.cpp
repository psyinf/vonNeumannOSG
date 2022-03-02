#include "SimpleScene.h"
#include "Entity.h"
#include <random>
#include <JsonConfigCache.h>
#include "SceneConfig.h"
#include "EntityBehavior.h"
#include "EntityBehaviorRegistry.h"
#include "EntityManager.h"


void SimpleScene::load(const std::string& fileName)
{
    std::shared_ptr<entities::EntityManager> entityManager    = std::make_unique<entities::EntityManager>();
	const auto scene = nsConfig::load<nsConfig::SceneConfig>(fileName);
	auto j = nlohmann::json(
		{
			{
				"box" ,
				{
					{ "min" , -500.0f }
					,{ "max" , 500.0f }
				}
			}
		});

	auto pid = nlohmann::json(
		{
			{
				"pid" ,
				{
					 0.001f 
					, 0.01f 
					, 0.01f 
				}
			}
		});
	

    //auto& registry = entityManager->getBehaviorRegistry();
    //registry.add(std::make_shared<entities::Torusifator>(j));
    //registry.add(std::make_shared<entities::Reflector(j))
	
	
	std::default_random_engine generator;
	std::normal_distribution vel_distribution(0.0, 3.0);
	std::normal_distribution pos_distribution(0.0, 100.0);
	size_t rows = std::sqrtl(scene.numDrones);
	size_t columns = scene.numDrones / rows;
	osg::BoundingSphere bounds;
	for (size_t i = scene.numDrones; i-- > 0;) {
        osg::ref_ptr<entities::Entity> model = new entities::Entity(std::format("drone{}",i), scene.defaultEntity, entityManager);
		if (bounds.radius() < 0) {
			bounds = model->getBound();
			std::cout << "Calculated bounds for model: " << bounds.radius() << std::endl;
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

