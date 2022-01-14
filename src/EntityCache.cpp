#include "EntityCache.h"

osg::ref_ptr<osg::Node> EntityCache::readNodeFile(const std::string& file)
{

	auto node =  osgDB::readNodeFile(file);
	node->setDataVariance(osg::Object::STATIC);
	return node;
	/*
	auto entry = nodeCache.find(file);
	if (entry == nodeCache.end()) {
		auto node = osgDB::readNodeFile(file);
		nodeCache.emplace(file, node);
		return node;
	}
	else {
		return (*entry).second;
	}
	}*/
}
