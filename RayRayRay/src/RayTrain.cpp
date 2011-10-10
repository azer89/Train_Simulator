
#include "Stdafx.h"
#include "RayTrain.h"
#include "Rail.h"
#include "OgreMath.h"

//-------------------------------------------------------------------------------------
RayTrain::RayTrain(Ogre::SceneManager* mSceneMgr, Rail* rail ): numTrain(0)
{
	this->timeSinceLastFrame = 0.0f;	// set to 0
	this->mSceneMgr = mSceneMgr;		// point to mSceneMgr
	this->rail = rail;					// point to rail
	this->isInitialized = false;		// init false
	this->isTrainMoving = false;		// not moving at the first time
	counterPoint = 0;					// counter 0
	trainDistance = 5;					// distance between train
}


//-------------------------------------------------------------------------------------
RayTrain::~RayTrain(void)
{	
}

//-------------------------------------------------------------------------------------
// Called every frame rendering
void RayTrain::update(Ogre::Real timeSinceLastFrame)
{
	// if not moving don't update anything
	if(!this->isTrainMoving) return;

	// accumulate time
	this->timeSinceLastFrame += timeSinceLastFrame;	

	// update 50 times per second (if the fps don't drop)
	if(this->timeSinceLastFrame >= 0.02f)	
	{
		this->timeSinceLastFrame = 0.0f;				// reset time accumulation
		int tSize = rail->tiePoints.size();				// get size
		if(counterPoint >= tSize) counterPoint = 0;		// keep up so won't get overindex 

		for(int a = 0; a < trainNodes.size(); a++)
		{			
			int aCPoint = counterPoint - (trainDistance * a);
			if(aCPoint < 0) aCPoint = tSize + aCPoint;
			
			Ogre::Vector3 v01 = rail->tiePoints[aCPoint];
			Ogre::Vector3 v02 = rail->tiePoints[(aCPoint + 1) % tSize];
			Ogre::Vector3 v03 = (v02 - v01);
			v03.normalise();

			trainNodes[a]->setDirection(v03, Ogre::SceneNode::TS_PARENT);
			trainNodes[a]->needUpdate();
			trainNodes[a]->setPosition(v01);			
		}

		counterPoint += 1;
	}
}

//-------------------------------------------------------------------------------------
// Called once to show up the train
void RayTrain::initTrain()
{
	this->isInitialized = true;
	Ogre::Vector3 v01 = rail->tiePoints[counterPoint];
	Ogre::Vector3 v02 = rail->tiePoints[(counterPoint + 1) % rail->tiePoints.size()];
	Ogre::Vector3 v03 = v02 - v01;
	//v03.y = 0;
	v03.normalise();
	
	char name[16];
	sprintf(name, "Train%d", numTrain++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "front_train.mesh");
	//ent->setDefaultQueryFlags(0xFFFFFFFF);
	ent->setCastShadows(true);	
	
	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", v01);
	mNode->attachObject(ent);

	mNode->setDirection(v03, Ogre::SceneNode::TS_WORLD);
	mNode->setFixedYawAxis(true);
	//mNode->needUpdate();
	mNode->scale(10.0f, 10.0f, 10.0f);

	this->trainNodes.push_back(mNode);
}

//-------------------------------------------------------------------------------------
// Start train to move
void RayTrain::startTrain()
{
	this->isTrainMoving = true;
}

//-------------------------------------------------------------------------------------
// Stop train movement
void RayTrain::stopTrain()
{
	this->isTrainMoving = false;
}

//-------------------------------------------------------------------------------------
// Reposition the trains when they stop
void RayTrain::repositionTrain(void)
{
	if(!this->isTrainMoving)
	{
		for(int a = 0; a < trainNodes.size(); a++)
		{
			int tSize = rail->tiePoints.size();
			if(counterPoint >= tSize) counterPoint = 0;
			int aCPoint = counterPoint - (trainDistance * a);
			if(aCPoint < 0) aCPoint = tSize + aCPoint;

			Ogre::Vector3 v01 = rail->tiePoints[aCPoint];
			Ogre::Vector3 v02 = rail->tiePoints[(aCPoint + 10) % tSize];
			Ogre::Vector3 v03 = (v02 - v01);
			v03.normalise();

			trainNodes[a]->setDirection(v03, Ogre::SceneNode::TS_PARENT);
			//trainNodes[a]->needUpdate();
			trainNodes[a]->setPosition(v01);
		}
	}
}

//-------------------------------------------------------------------------------------
// Add train, max 10
void RayTrain::addTrain()
{
	int tSize = rail->tiePoints.size();
	if(tSize == 10) return;

	int aCPoint = counterPoint - (trainDistance * numTrain);
	if(aCPoint < 0) aCPoint = tSize + aCPoint;

	Ogre::Vector3 v01 = rail->tiePoints[aCPoint];
	Ogre::Vector3 v02 = rail->tiePoints[(aCPoint + 1) % rail->tiePoints.size()];
	Ogre::Vector3 v03 = v02 - v01;
	v03.normalise();

	char name[16];
	sprintf(name, "Train%d", numTrain++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "back_train.mesh");
	//ent->setDefaultQueryFlags(0xFFFFFFFF);
	ent->setCastShadows(true);	

	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", v01);
	mNode->attachObject(ent);

	mNode->setDirection(Ogre::Vector3::UNIT_Z, Ogre::SceneNode::TS_PARENT);
	mNode->setFixedYawAxis(true);
	mNode->scale(10.0f, 10.0f, 10.0f);

	this->trainNodes.push_back(mNode);
}

//-------------------------------------------------------------------------------------
// Delete train at the end
void RayTrain::deleteTrain()
{
	Ogre::SceneNode* lastNode = trainNodes[trainNodes.size() - 1];			// find the last node
	this->mSceneMgr->getRootSceneNode()->removeChild(lastNode->getName());	// delete it by name
	trainNodes.pop_back();													// remove from list
}


