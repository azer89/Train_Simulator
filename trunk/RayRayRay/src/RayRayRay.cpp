/*
-----------------------------------------------------------------------------
Filename:    RayRayRay.cpp
Author:      Reza Adhitya Saputra
-----------------------------------------------------------------------------

This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC9 (July 2011)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/

#include "RayRayRay.h"

//-------------------------------------------------------------------------------------
RayRayRay::RayRayRay(void):
	mCount(0),
	mCurrentObject(0),
	bLMouseDown(false),
	bRMouseDown(false),
	mRotateSpeed(0.1f),
	bRobotMode(true),
	hideTray(false)
{
}
//-------------------------------------------------------------------------------------
RayRayRay::~RayRayRay(void)
{
	mSceneMgr->destroyQuery(mRayScnQuery);
}

//-------------------------------------------------------------------------------------
void RayRayRay::destroyScene(void)
{
	OGRE_DELETE mTerrainGroup;
    OGRE_DELETE mTerrainGlobals;
}
//-------------------------------------------------------------------------------------
void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	img.load("terrain.png", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX) img.flipAroundY();
    if (flipY) img.flipAroundX();
	
}
//-------------------------------------------------------------------------------------
void RayRayRay::defineTerrain(long x, long y)
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }
}
//-------------------------------------------------------------------------------------
void RayRayRay::initBlendMaps(Ogre::Terrain* terrain)
{
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 40;
    Ogre::Real fadeDist0 = 20;
    Ogre::Real minHeight1 = 20;
    Ogre::Real fadeDist1 = 5;
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;
 
            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
 
            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}
//-------------------------------------------------------------------------------------
void RayRayRay::configureTerrainDefaults(Ogre::Light* light)
{
	// Configure global
    mTerrainGlobals->setMaxPixelError(8);
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000);
 
    // Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());
 
    // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 65;
    defaultimp.worldSize = 1000.0f;
	defaultimp.inputScale = 100;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
    // textures
	
    defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 100;
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 200;
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");
	
	/*
	defaultimp.layerList.resize(1);
    defaultimp.layerList[0].worldSize = 30;
    defaultimp.layerList[0].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("grass_green-01_normalheight.dds");
	*/
}
 
//-------------------------------------------------------------------------------------
void RayRayRay::createScene(void)
{
	// set camera
	mCamera->setPosition(Ogre::Vector3(357, 70, 171));
    mCamera->lookAt(Ogre::Vector3(357, 80, 200));
    mCamera->setNearClipDistance(5);
    mCamera->setFarClipDistance(50000);
 
    if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
    {
        mCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
    }
	 
	// Play with startup Texture Filtering options
	// Note: Pressing T on runtime will discarde those settings
	//  Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	//  Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(7);
 
    Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
    lightdir.normalise();
 
    Ogre::Light* light = mSceneMgr->createLight("tstLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
 
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
 
    mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
 
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 65, 1000.f);
    mTerrainGroup->setFilenameConvention(Ogre::String("RayRayRay"), Ogre::String("dat"));
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);

    configureTerrainDefaults(light);
 
    for (long x = 0; x <= 0; ++x)
        for (long y = 0; y <= 0; ++y)
            defineTerrain(x, y);
 
    // sync load since we want everything in place when we start
    mTerrainGroup->loadAllTerrains(true);
 
    if (mTerrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
        while(ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
            initBlendMaps(t);
        }
    }
 
    mTerrainGroup->freeTemporaryResources();

    Ogre::Plane plane;
    plane.d = 100;
    plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
 
    //mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8, 500);
	mSceneMgr->setSkyPlane(true, plane, "Examples/CloudySky", 50, 10 , true, 0.7, 10, 10); 
	
	//CEGUI setup
	mGUIRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
 
	//show the CEGUI cursor
	CEGUI::SchemeManager::getSingleton().create((CEGUI::utf8*)"WindowsLook.scheme");
	CEGUI::MouseCursor::getSingleton().setImage("WindowsLook", "MouseArrow");
}
 
void RayRayRay::chooseSceneManager(void)
{
	//create a scene manager that is meant for handling outdoor scenes
	mSceneMgr = mRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE);
}
 
void RayRayRay::createFrameListener(void)
{
	//we still want to create the frame listener from the base app
	BaseApplication::createFrameListener();

	mInfoLabel = mTrayMgr->createLabel(OgreBites::TL_TOP, "TInfo", "", 350);
 
	//but we also want to set up our raySceneQuery after everything has been initialized
	mRayScnQuery = mSceneMgr->createRayQuery(Ogre::Ray());
}
 
bool RayRayRay::frameRenderingQueued(const Ogre::FrameEvent& arg)
{
	//we want to run everything in the previous frameRenderingQueued call
	//but we also want to do something afterwards, so lets  start off with this
	if(!BaseApplication::frameRenderingQueued(arg))
	{
		return false;
	}

	// hide 
	if(!hideTray)
	{
		mTrayMgr->hideLogo();
		mTrayMgr->toggleAdvancedFrameStats();
		hideTray = true;
	}

	// This next big chunk basically sends a raycast straight down from the camera's position
	// It then checks to see if it is under world geometry and if it is we move the camera back up
	Ogre::Vector3 camPos = mCamera->getPosition();
	Ogre::Terrain* pTerrain = mTerrainGroup->getTerrain(0, 0);
	Ogre::Ray mouseRay(Ogre::Vector3(camPos.x, 5000.0f, camPos.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
    std::pair <bool, Ogre::Vector3> test;
    test = pTerrain->rayIntersects(mouseRay, true, 0);

	if (test.first) 
	{
		//gets the results, fixes camera height
		Ogre::Real terrainHeight = test.second.y;
		if((terrainHeight + 10.0f) > camPos.y)
		{
			mCamera->setPosition(camPos.x, terrainHeight + 10.0f, camPos.z);
		}			
	}


	if (mTerrainGroup->isDerivedDataUpdateInProgress())
    {
        mTrayMgr->moveWidgetToTray(mInfoLabel, OgreBites::TL_TOP, 0);
        mInfoLabel->show();
        if (mTerrainsImported)
        {
            mInfoLabel->setCaption("Building terrain, please wait...");
        }
        else
        {
            mInfoLabel->setCaption("Updating textures, patience...");
        }
    }
    else
    {
        mTrayMgr->removeWidgetFromTray(mInfoLabel);
        mInfoLabel->hide();
        if (mTerrainsImported)
        {
            mTerrainGroup->saveAllTerrains(true);
            mTerrainsImported = false;
        }
    }
 
	return true;
}
 
bool RayRayRay::mouseMoved(const OIS::MouseEvent& arg)
{
	//updates CEGUI with mouse movement
	CEGUI::System::getSingleton().injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
 
	//if the left mouse button is held down
	if(bLMouseDown)
	{
		//find the current mouse position
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
 
		//create a raycast straight out from the camera at the mouse's location
		Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
		
		Ogre::Vector3 camPos = mCamera->getPosition();
		Ogre::Terrain* pTerrain = mTerrainGroup->getTerrain(0, 0);
		std::pair <bool, Ogre::Vector3> test;
		test = pTerrain->rayIntersects(mouseRay, true, 0);

		if (test.first) 
		{
			mCurrentObject->setPosition(test.second);
		}

		/*
		mRayScnQuery->setRay(mouseRay);
		mRayScnQuery->setSortByDistance(false);	//world geometry is at the end of the list if we sort it, so lets not do that
 
		Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
		Ogre::RaySceneQueryResult::iterator iter = result.begin();
 
		//check to see if the mouse is pointing at the world and put our current object at that location
		for(iter; iter != result.end(); iter++)
		{
			if(iter->worldFragment)
			{
				mCurrentObject->setPosition(iter->worldFragment->singleIntersection);
				break;
			}	
		}
		*/
	}
	else if(bRMouseDown)	//if the right mouse button is held down, be rotate the camera with the mouse
	{
		mCamera->yaw(Ogre::Degree(-arg.state.X.rel * mRotateSpeed));
		mCamera->pitch(Ogre::Degree(-arg.state.Y.rel * mRotateSpeed));
	}
 
	return true;
}
 
bool RayRayRay::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left)
	{
		//show that the current object has been deselected by removing the bounding box visual
		if(mCurrentObject)
		{
			mCurrentObject->showBoundingBox(false);
		}
 
		//find the current mouse position
		CEGUI::Point mousePos = CEGUI::MouseCursor::getSingleton().getPosition();
 
		//then send a raycast straight out from the camera at the mouse's position
		Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(mousePos.d_x/float(arg.state.width), mousePos.d_y/float(arg.state.height));
		mRayScnQuery->setRay(mouseRay);
		mRayScnQuery->setSortByDistance(true);
		mRayScnQuery->setQueryMask(bRobotMode ? ROBOT_MASK : NINJA_MASK);	//will return objects with the query mask in the results
 
		// create rayIntersect fro TerrainGroup
		Ogre::Terrain* pTerrain = mTerrainGroup->getTerrain(0, 0);
		std::pair <bool, Ogre::Vector3> test;
		test = pTerrain->rayIntersects(mouseRay, true, 0);
		
		//This next chunk finds the results of the raycast
		//If the mouse is pointing at world geometry we spawn a robot at that position
		Ogre::RaySceneQueryResult& result = mRayScnQuery->execute();
		Ogre::RaySceneQueryResult::iterator iter = result.begin();

		for(iter; iter != result.end(); iter++)
		{
			//if you clicked on a robot or ninja it becomes selected
			if(iter->movable && iter->movable->getName().substr(0, 5) != "tile[")
			{
				mCurrentObject = iter->movable->getParentSceneNode();
				break;
			}
		}

		if(test.first)
		{
			char name[16];
			Ogre::Entity* ent;

			//if we are in robot mode we spawn a robot at the mouse location
			if(bRobotMode)
			{
				sprintf(name, "Robot%d", mCount++);
				ent = mSceneMgr->createEntity(name, "robot.mesh");
				ent->setQueryFlags(ROBOT_MASK);
			}
			//otherwise we spawn a ninja
			else
			{
				sprintf(name, "Ninja%d", mCount++);
				ent = mSceneMgr->createEntity(name, "ninja.mesh");
				ent->setQueryFlags(NINJA_MASK);

			}
			//attach the object to a scene node
			mCurrentObject = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", test.second);
			mCurrentObject->attachObject(ent);

			//lets shrink the object, only because the terrain is pretty small
			mCurrentObject->setScale(0.2f, 0.2f, 0.2f);
		}
 
		//now we show the bounding box so the user can see that this object is selected
		if(mCurrentObject)
		{
			mCurrentObject->showBoundingBox(true);
		}
 
		bLMouseDown = true;
	}
	else if(id == OIS::MB_Right)	// if the right mouse button is held we hide the mouse cursor for view mode
	{
		CEGUI::MouseCursor::getSingleton().hide();
		bRMouseDown = true;
	}
 
	return true;
}
 
bool RayRayRay::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	if(id  == OIS::MB_Left)
	{
		bLMouseDown = false;
	}
	else if(id == OIS::MB_Right)	//when the right mouse is released we then unhide the cursor
	{
		CEGUI::MouseCursor::getSingleton().show();
		bRMouseDown = false;
	}
	return true;
}
 
bool RayRayRay::keyPressed(const OIS::KeyEvent& arg)
{
	//check and see if the spacebar was hit, and this will switch which mesh is spawned
	if(arg.key == OIS::KC_SPACE)
	{
		bRobotMode = !bRobotMode;
	}
 
	//then we return the base app keyPressed function so that we get all of the functionality
	//and the return value in one line
	return BaseApplication::keyPressed(arg);
}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        RayRayRay app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
