#include "SimpleScene.h"
#include "Entity.h"
#include <random>
#include "ConfigCache.h"
#include "SceneConfig.h"
#include "EntityBehavior.h"

void SimpleScene::load(const std::string& fileName)
{
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
	nsEntities::BehaviorRegistry::add(std::make_shared<nsEntities::Reflector>(j));
	nsEntities::BehaviorRegistry::add(std::make_shared<nsEntities::PositionController>(pid));
	nsEntities::BehaviorRegistry::add(std::make_shared<nsEntities::Torusifator>(j));

	std::default_random_engine generator;
	std::normal_distribution<double> vel_distribution(0.0, 3.0);
	std::normal_distribution<double> pos_distribution(0.0, 100.0);
	size_t rows = std::sqrtl(scene.numDrones);
	size_t columns = scene.numDrones / rows;
	osg::BoundingSphere bounds;
	for (size_t i = scene.numDrones; i-- > 0;) {

		osg::ref_ptr<nsEntities::Entity> model
			= new nsEntities::Entity(scene.defaultEntity);
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

