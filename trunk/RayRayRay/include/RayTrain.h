
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "Stdafx.h"
#include "Rail.h"


class RayTrain
{
public:
	RayTrain(Ogre::SceneManager* mSceneMgr, Rail* rail );
	virtual ~RayTrain(void);

	Ogre::SceneManager* mSceneMgr;
	Rail* rail;
};