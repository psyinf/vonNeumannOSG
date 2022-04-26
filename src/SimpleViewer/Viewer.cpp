/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2010 Robert Osfield
 *
 * This application is open source and may be redistributed and/or modified
 * freely and without restriction, both in commercial and non commercial applications,
 * as long as this copyright notice is maintained.
 *
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "SimpleScene.h"

#include <osg/CoordinateSystemNode>
#include <osg/Switch>
#include <osg/Types>
#include <osgDB/ReadFile>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/Device>
#include <osgGA/DriveManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/SphericalManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/TrackballManipulator>
#include <osgText/Text>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <iostream>
#include <memory>


void setupCaching()
{
    // setup sharing
    if (true)
    {
        osgDB::SharedStateManager::ShareMode mode = osgDB::SharedStateManager::SHARE_NONE; // = osgDB::SharedStateManager::SHARE_ALL;

        mode = static_cast<osgDB::SharedStateManager::ShareMode>(mode | osgDB::SharedStateManager::SHARE_STATESETS);
        mode = static_cast<osgDB::SharedStateManager::ShareMode>(mode | osgDB::SharedStateManager::SHARE_TEXTURES);

        osgDB::Registry::instance()->getOrCreateSharedStateManager()->setShareMode(mode);
    }
    osgDB::Registry::instance()->getDataFilePathList().emplace_back("data");

    osgDB::ReaderWriter::Options* opt = osgDB::Registry::instance()->getOptions();
    if (opt == NULL)
    {
        opt = new osgDB::ReaderWriter::Options();
    }

    // if (getConfigRef().mGlobalState.mObjectCaching)
    {
        // setup caching
        osgDB::Options::CacheHintOptions opts = osgDB::Options::CACHE_ARCHIVES;
        opts                                  = static_cast<osgDB::Options::CacheHintOptions>(opts | osgDB::Options::CACHE_IMAGES);
        opts                                  = static_cast<osgDB::Options::CacheHintOptions>(opts | osgDB::Options::CACHE_NODES);
        opts                                  = static_cast<osgDB::Options::CacheHintOptions>(opts | osgDB::Options::CACHE_OBJECTS);
        opt->setObjectCacheHint(static_cast<osgDB::Options::CacheHintOptions>(opts));
        osgDB::Registry::instance()->setOptions(opt);
    }
    // setup importer options
    {
        std::string completeOptionsString;

        // options->setOptionString("noLoadExternalReferenceFiles");

        completeOptionsString.append("noTexturesInIVEFile ");
        completeOptionsString.append("billboardCenter ");
        // completeOptionsString.append("dofAnimation ");
        completeOptionsString.append("readObjectRecordData ");
        completeOptionsString.append("noTexturesInIVEFile ");
        // completeOptionsString+="preserveFace ";
        // completeOptionsString.append("preserveObject ");
        completeOptionsString.append("preserveNonOsgAttrsAsUserData ");
        completeOptionsString.append("noTextureAlphaForTransparancyBinning ");
        /*
        completeOptionsString+="dds_flip ";
        completeOptionsString+="dds_dxt1_detect_rgba ";
        */
        // completeOptionsString+="keepExternalReferences ";
        // completeOptionsString+="ddsNoAutoFlipWrite ";
        opt->setOptionString(completeOptionsString);
        osgDB::Registry::instance()->setOptions(opt);
    }
}

class KeyEventHandler : public osgGA::GUIEventHandler
{
public:
    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*) override
    {
        switch (ea.getEventType())
        {
        case osgGA::GUIEventAdapter::KEYDOWN:
            switch (ea.getKey())
            {
            case '.':
                // case 'W':
                factor *= 1.1;
                return true;
                break;
            case ',':
                // case 'S':
                factor /= 1.1;
                return true;
                break;
            case osgGA::GUIEventAdapter::KEY_Return:
                paused = !paused;
                break;
            }

            break;
        default:
            break;
        }
        return false;
    }

    float getFactor()
    {
        return paused ? 0.0 : factor;
    }

protected:
    float factor = 1.0;
    bool  paused = true;
};

int main(int argc, char** argv)
try
{
    osgViewer::Viewer viewer;


    // set up the camera manipulators.
    {
        osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

        keyswitchManipulator->addMatrixManipulator('1', "Trackball", new osgGA::TrackballManipulator());
        keyswitchManipulator->addMatrixManipulator('2', "Flight", new osgGA::FlightManipulator());
        keyswitchManipulator->addMatrixManipulator('3', "Drive", new osgGA::DriveManipulator());
        keyswitchManipulator->addMatrixManipulator('4', "Terrain", new osgGA::TerrainManipulator());
        keyswitchManipulator->addMatrixManipulator('5', "Orbit", new osgGA::OrbitManipulator());
        keyswitchManipulator->addMatrixManipulator('6', "FirstPerson", new osgGA::FirstPersonManipulator());
        keyswitchManipulator->addMatrixManipulator('7', "Spherical", new osgGA::SphericalManipulator());
        viewer.setCameraManipulator(keyswitchManipulator.get());
    }

    // add the state manipulator
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
    // add the thread model handler
    viewer.addEventHandler(new osgViewer::ThreadingHandler);
    // add the window size toggle handler
    viewer.addEventHandler(new osgViewer::WindowSizeHandler);
    // add the stats handler
    viewer.addEventHandler(new osgViewer::StatsHandler);
    auto keyEventHandler = new KeyEventHandler;
    viewer.addEventHandler(keyEventHandler);

    // load the data
    setupCaching();
    std::unique_ptr<SimpleScene> ss = std::make_unique<SimpleScene>();
    ss->load("data/scene.json");


    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    // optimizer.optimize(ss->getSceneRoot(), osgUtil::Optimizer::DEFAULT_OPTIMIZATIONS);

    viewer.setSceneData(ss->getSceneRoot());
    viewer.getCamera()->setComputeNearFarMode(osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR);
    viewer.setUpViewInWindow(100, 100, 1024, 1024);
    viewer.realize();

    while (!viewer.done())
    {

        double last_stamp_rt = viewer.getFrameStamp()->getReferenceTime();
        double last_stamp_st = viewer.getFrameStamp()->getSimulationTime();
        viewer.advance(); // ref time increase
        double time_elapsed_rt = viewer.getFrameStamp()->getReferenceTime() - last_stamp_rt;
        viewer.getFrameStamp()->setSimulationTime(last_stamp_st + (time_elapsed_rt * keyEventHandler->getFactor()));
        viewer.eventTraversal();
        viewer.updateTraversal();

        viewer.renderingTraversals();
    }
}
catch (const std::exception& e)
{
    std::cout << e.what() << std::endl;
}