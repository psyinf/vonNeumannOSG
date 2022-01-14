#pragma once

#include <osg/Node>
#include <osg/Group>

#include "Entity.h"


class SimpleScene {
	const std::string default_model = R"(data/drone2.obj)";
public:
	void load(const std::string& fileName);

	osg::Group* getSceneRoot() {
		return root;
	}


protected:
	osg::ref_ptr<osg::Group> root = new osg::Group();


};