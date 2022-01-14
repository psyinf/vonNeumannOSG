#pragma once
#include <osg/Node>
#include <osgDB/ReadFile>
class EntityCache {
public:
    static osg::ref_ptr<osg::Node> readNodeFile(const std::string& file);
    inline static std::map<std::string, osg::ref_ptr<osg::Node>> nodeCache = {};

};