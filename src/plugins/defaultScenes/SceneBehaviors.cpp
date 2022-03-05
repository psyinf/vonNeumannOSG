#pragma once
#include "Entity.h"
#include "SceneBehaviors.h"
#include "Vec3dPid.h"
#include <nlohmann/json.hpp>

using namespace entities;



Reflector::Reflector(const BehaviorConf& conf) 
	:BehaviorBase(conf)
{
	const float minSize = conf.conf["box"]["min"];
	const float maxSize = conf.conf["box"]["max"];
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


Torusifator::Torusifator(const BehaviorConf& conf)
	:BehaviorBase(conf)
{
	const float minSize = conf.conf["box"]["min"];
	const float maxSize = conf.conf["box"]["max"];
	box._min = osg::Vec3(1, 1, 1) * minSize;
	box._max = osg::Vec3(1, 1, 1) * maxSize;
}


void Torusifator::frame(Entity& entity, FrameTime frameTime)
{
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


