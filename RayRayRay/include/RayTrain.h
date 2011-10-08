
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>

#include "Stdafx.h"
#include "ClassDefine.h"

class RayTrain
{
public:
	RayTrain(Ogre::SceneManager* mSceneMgr, Rail* rail );
	virtual ~RayTrain(void);
	
	bool isInitialized;	
	
	void initTrain(void);							// create main train
	void startTrain(void);							// start train
	void stopTrain(void);							// stop terrain
	void update(Ogre::Real timeSinceLastFrame);		// update the train per milisecond
	void addTrain(void);							// add train
	void deleteTrain(void);							// add train
	void repositionTrain(void);						// necessary when updating the track so the train won't out of track

private:
	int trainDistance;
	bool isTrainMoving;
	Ogre::SceneManager* mSceneMgr;
	std::vector<Ogre::SceneNode*> trainNodes;
	Rail* rail;
	Ogre::Real timeSinceLastFrame;
	int numTrain;
	int counterPoint;
};