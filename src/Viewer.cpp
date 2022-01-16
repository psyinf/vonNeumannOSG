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

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/CoordinateSystemNode>

#include <osg/Switch>
#include <osg/Types>
#include <osgText/Text>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>
#include <osgGA/SphericalManipulator>

#include <osgGA/Device>

#include <iostream>
#include <memory>
#include "SimpleScene.h"


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

    //if (getConfigRef().mGlobalState.mObjectCaching)
    {
        //setup caching
        osgDB::Options::CacheHintOptions opts = osgDB::Options::CACHE_ARCHIVES;
        opts = static_cast<osgDB::Options::CacheHintOptions>(opts | osgDB::Options::CACHE_IMAGES);
        opts = static_cast<osgDB::Options::CacheHintOptions>(opts | osgDB::Options::CACHE_NODES);
        opts = static_cast<osgDB::Options::CacheHintOptions>(opts | osgDB::Options::CACHE_OBJECTS);
       opt->setObjectCacheHint(static_cast<osgDB::Options::CacheHintOptions>(opts));
        osgDB::Registry::instance()->setOptions(opt);
    }
    //setup importer options
    {
        std::string completeOptionsString;
        
        //options->setOptionString("noLoadExternalReferenceFiles");

        completeOptionsString.append("noTexturesInIVEFile ");
        completeOptionsString.append("billboardCenter ");
        //completeOptionsString.append("dofAnimation ");
        completeOptionsString.append("readObjectRecordData ");
        completeOptionsString.append("noTexturesInIVEFile ");
        //completeOptionsString+="preserveFace ";
        //completeOptionsString.append("preserveObject ");
        completeOptionsString.append("preserveNonOsgAttrsAsUserData ");
        completeOptionsString.append("noTextureAlphaForTransparancyBinning ");
        /*
        completeOptionsString+="dds_flip ";
        completeOptionsString+="dds_dxt1_detect_rgba ";
        */
        //completeOptionsString+="keepExternalReferences ";
        //completeOptionsString+="ddsNoAutoFlipWrite ";
        opt->setOptionString(completeOptionsString);
        osgDB::Registry::instance()->setOptions(opt);
    }

   
}

int main(int argc, char** argv) try
{
    osgViewer::Viewer viewer;


    // set up the camera manipulators.
    {
        osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

        keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
        keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
        keyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
        keyswitchManipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );
        keyswitchManipulator->addMatrixManipulator( '5', "Orbit", new osgGA::OrbitManipulator() );
        keyswitchManipulator->addMatrixManipulator( '6', "FirstPerson", new osgGA::FirstPersonManipulator() );
        keyswitchManipulator->addMatrixManipulator('7', "Spherical", new osgGA::SphericalManipulator());
        viewer.setCameraManipulator( keyswitchManipulator.get() );
    }

    // add the state manipulator
    viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
     // add the thread model handler
    viewer.addEventHandler(new osgViewer::ThreadingHandler);
    // add the window size toggle handler
    viewer.addEventHandler(new osgViewer::WindowSizeHandler);
    // add the stats handler
    viewer.addEventHandler(new osgViewer::StatsHandler);
    // add the record camera path handler
    viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
    // add the LOD Scale handler
    viewer.addEventHandler(new osgViewer::LODScaleHandler);
    // add the screen capture handler
    viewer.addEventHandler(new osgViewer::ScreenCaptureHandler);
    // load the data
    setupCaching();
    std::unique_ptr<SimpleScene> ss = std::make_unique<SimpleScene>();
    ss->load("data/scene.json");


    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    //optimizer.optimize(ss->getSceneRoot(), osgUtil::Optimizer::DEFAULT_OPTIMIZATIONS);

    viewer.setSceneData(ss->getSceneRoot());

    viewer.realize();

    return viewer.run();

}
catch (const std::exception& e){
    std::cout << e.what() << std::endl;
}