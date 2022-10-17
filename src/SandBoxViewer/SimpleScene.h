#pragma once

#include <osg/Node>
#include <osg/Group>

namespace entities
{
class EntityManager;
}


class SimpleScene {
	const std::string default_model = R"(data/drone2.obj)";
public:
	SimpleScene() = default;
    virtual ~SimpleScene() = default;
	void load(const std::string& fileName);

	osg::Group* getSceneRoot();


private:
	osg::ref_ptr<osg::Group> root = new osg::Group();
   


};