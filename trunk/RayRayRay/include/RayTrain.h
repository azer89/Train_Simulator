
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "Stdafx.h"
#include "ClassDefine.h"
//#include "RayRayRay.h"
//#include "Rail.h"
//#include "Rail.h"


class RayTrain
{
public:
	RayTrain(Ogre::SceneManager* mSceneMgr, Rail* rail );
	virtual ~RayTrain(void);
	
	bool isInitialized;	
	
	void initTrain();
	void startTrain();
	void stopTrain();
	void update(Ogre::Real timeSinceLastFrame);

private:
	bool isTrainMoving;
	Ogre::SceneManager* mSceneMgr;
	std::vector<Ogre::SceneNode*> trainNodes;
	Rail* rail;
	Ogre::Real timeSinceLastFrame;
	int numTrain;
	int counterPoint;
};