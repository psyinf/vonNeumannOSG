#pragma once
#include "Entity.h"
#include "EntityBehavior.h"
#include "Vec3dPid.h"
#include <nlohmann/json.hpp>
using namespace nsEntities;


void EntityBehavior::frame(Entity& entity, FrameTime frameTime)
{
	std::for_each(std::cbegin(behaviors), std::cend(behaviors), [&](auto b) {b->frame(entity, frameTime); });
	
}


Reflector::Reflector(const Config& conf) 
	:BehaviorBase("reflector")
{
	float minSize = conf["box"]["min"];
	float maxSize = conf["box"]["max"];
	box._min = osg::Vec3(1, 1, 1) * minSize;
	box._max = osg::Vec3(1, 1, 1) * maxSize;
}


void Reflector::frame(Entity& entity, FrameTime frameTime)
{
	auto& velocity = entity.getVelocity();
	osg::Vec3d trans = entity.getPosition();
	if (trans.x() > box.xMax()) {
		trans.x() = box.xMax();
		velocity.x() = -velocity.x();
	}
	else if (trans.x() < box.xMin()) {
		trans.x() = box.xMin();
		velocity.x() = -velocity.x();
	}

	if (trans.y() > box.yMax()) {
		trans.y() = box.yMax();
		velocity.y() = -velocity.y();
	}
	else if (trans.y() < box.yMin()) {
		trans.y() = box.yMin();
		velocity.y() = -velocity.y();
	}

	if (trans.z() > box.zMax()) {
		trans.z() = box.zMax();
		velocity.z() = -velocity.z();
	}
	else if (trans.z() < box.zMin()) {
		trans.z() = box.zMin();
		velocity.z() = -velocity.z();
	}
	entity.setPosition(trans);
}

void PositionController::frame(Entity& entity, FrameTime frameTime)
{
	entity.getAcceleration() = pidController.calculate(entity.getTarget(), entity.getPosition(), frameTime);
	//std::cout << pidController.getPreError().length() << std::endl;
}

std::shared_ptr<StateFullBehavior> PositionController::clone(const nsEntities::BehaviorConf& conf)
{
	return std::make_shared<PositionController>(conf.conf);
}

PositionController::PositionController(const Config& conf) 
	:StateFullBehavior("position")
{
	const auto& pid = conf["pid"];
	pidController.setPid(osg::Vec3d(pid[0], pid[1], pid[2]));

}

Torusifator::Torusifator(const Config& conf)
	:BehaviorBase("torus")
{
	float minSize = conf["box"]["min"];
	float maxSize = conf["box"]["max"];
	box._min = osg::Vec3(1, 1, 1) * minSize;
	box._max = osg::Vec3(1, 1, 1) * maxSize;
}


void Torusifator::frame(Entity& entity, FrameTime frameTime)
{
	auto& velocity = entity.getVelocity();
	osg::Vec3d trans = entity.getPosition();
	if (trans.x() > box.xMax()) {
		trans.x() = box.xMin();
	}
	else if (trans.x() < box.xMin()) {
		trans.x() = box.xMax();
	}

	if (trans.y() > box.yMax()) {
		trans.y() = box.yMin();
	}
	else if (trans.y() < box.yMin()) {
		trans.y() = box.yMax();
	}

	if (trans.z() > box.zMax()) {
		trans.z() = box.zMin();
	}
	else if (trans.z() < box.zMin()) {
		trans.z() = box.zMax();
	}
	entity.setPosition(trans);
}

