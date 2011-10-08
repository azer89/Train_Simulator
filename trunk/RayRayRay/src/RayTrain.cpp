
#include "Stdafx.h"
#include "RayTrain.h"
#include "Rail.h"

//-------------------------------------------------------------------------------------
RayTrain::RayTrain(Ogre::SceneManager* mSceneMgr, Rail* rail ): numTrain(0)
{
	this->timeSinceLastFrame = 0.0f;
	this->mSceneMgr = mSceneMgr;
	this->rail = rail;
	this->isInitialized = false;
	this->isTrainMoving = false;
	counterPoint = 0;
	trainDistance = 5;
}


//-------------------------------------------------------------------------------------
RayTrain::~RayTrain(void)
{	
}

//-------------------------------------------------------------------------------------
void RayTrain::update(Ogre::Real timeSinceLastFrame)
{
	using namespace Ogre;

	if(!this->isTrainMoving) return;

	this->timeSinceLastFrame += timeSinceLastFrame;
	if(this->timeSinceLastFrame >= 0.02f)
	{
		this->timeSinceLastFrame = 0.0f;
		int tSize = rail->tiePoints.size();
		if(counterPoint >= tSize) counterPoint = 0;

		for(int a = 0; a < trainNodes.size(); a++)
		{			
			int aCPoint = counterPoint - (trainDistance * a);
			if(aCPoint < 0) aCPoint = tSize + aCPoint;
			
			Ogre::Vector3 v01 = rail->tiePoints[aCPoint];
			Ogre::Vector3 v02 = rail->tiePoints[(aCPoint + 1) % tSize];
			Ogre::Vector3 v03 = (v02 - v01);
			v03.y = 0;
			v03.normalise();
			

			trainNodes[a]->setDirection(v03, SceneNode::TS_PARENT);
			//trainNodes[a]->
			trainNodes[a]->setPosition(v01);			
		}

		counterPoint += 1;
	}
}

//-------------------------------------------------------------------------------------
void RayTrain::initTrain()
{
	this->isInitialized = true;
	Ogre::Vector3 initPos = rail->tiePoints[counterPoint];
	Ogre::Vector3 secPos = rail->tiePoints[(counterPoint + 1) % rail->tiePoints.size()];
	Ogre::Vector3 thiPos = secPos - initPos;
	thiPos.normalise();
	
	char name[16];
	sprintf(name, "Train%d", numTrain++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "front_train.mesh");
	//ent->setDefaultQueryFlags(0xFFFFFFFF);
	ent->setCastShadows(true);	
	
	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", initPos);
	mNode->attachObject(ent);
	mNode->setDirection(thiPos, Ogre::SceneNode::TS_PARENT);
	mNode->scale(10.0f, 10.0f, 10.0f);

	this->trainNodes.push_back(mNode);
}

//-------------------------------------------------------------------------------------
void RayTrain::startTrain()
{
	this->isTrainMoving = true;
}

//-------------------------------------------------------------------------------------
void RayTrain::stopTrain()
{
	this->isTrainMoving = false;
}

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
			v03.y = 0;
			v03.normalise();

			trainNodes[a]->setDirection(v03, Ogre::SceneNode::TS_PARENT);
			trainNodes[a]->setPosition(v01);
		}
	}
}

//-------------------------------------------------------------------------------------
void RayTrain::addTrain()
{
	int tSize = rail->tiePoints.size();
	if(tSize == 10) return;

	int aCPoint = counterPoint - (trainDistance * numTrain);
	if(aCPoint < 0) aCPoint = tSize + aCPoint;

	Ogre::Vector3 initPos = rail->tiePoints[aCPoint];
	Ogre::Vector3 secPos = rail->tiePoints[(aCPoint + 1) % rail->tiePoints.size()];
	Ogre::Vector3 thiPos = secPos - initPos;
	thiPos.y = 0;
	thiPos.normalise();

	char name[16];
	sprintf(name, "Train%d", numTrain++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "back_train.mesh");
	//ent->setDefaultQueryFlags(0xFFFFFFFF);
	ent->setCastShadows(true);	

	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", initPos);
	mNode->attachObject(ent);
	
	mNode->setDirection(thiPos, Ogre::SceneNode::TS_LOCAL);
	mNode->scale(10.0f, 10.0f, 10.0f);

	this->trainNodes.push_back(mNode);
}

//-------------------------------------------------------------------------------------
void RayTrain::deleteTrain()
{
	Ogre::SceneNode* lastNode = trainNodes[trainNodes.size() - 1];
	this->mSceneMgr->getRootSceneNode()->removeChild(lastNode->getName());
}


