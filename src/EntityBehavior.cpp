#pragma once
#include "Entity.h"
#include "EntityBehavior.h"
#include "Vec3dPid.h"
using namespace nsEntities;


void EntityBehavior::frame(Entity& entity, float frame_time)
{
	float dim = 1000;
	reflectInsideBox(entity, osg::BoundingBox(osg::Vec3(-dim,-dim,-dim), osg::Vec3(dim,dim,dim)));
	entity.getVelocity() += pidController.calculate(osg::Vec3d(0.1, 0, 0), entity.getPosition(), frame_time);
}

void EntityBehavior::reflectInsideBox(Entity& entity, const osg::BoundingBox& box)
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



