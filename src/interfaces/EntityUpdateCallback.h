#pragma once
#include <osg/NodeCallback>
#include <osg/FrameStamp>

class EntityUpdateCallback : public osg::NodeCallback
{
public:
	EntityUpdateCallback() = default;

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv);
protected:
	osg::FrameStamp lastFrame;
};