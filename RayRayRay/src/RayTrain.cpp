
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
		
		for(int a = 0; a < trainNodes.size(); a++)
		{
			int tSize = rail->tiePoints.size();
			if(counterPoint >= tSize) counterPoint = 0;
			
			Ogre::Vector3 v01 = rail->tiePoints[counterPoint];
			Ogre::Vector3 v02 = rail->tiePoints[(counterPoint + 1) % tSize];
			Ogre::Vector3 v03 = (v02 - v01);
			v03.normalise();

			trainNodes[a]->setDirection(v03, SceneNode::TS_PARENT);
			trainNodes[a]->setPosition(v01);
			
			counterPoint += 1;
		}
	}
}

//-------------------------------------------------------------------------------------
void RayTrain::initTrain()
{
	this->isInitialized = true;
	Ogre::Vector3 initPos = rail->tiePoints[counterPoint];
	
	char name[16];
	sprintf(name, "Train%d", numTrain++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "front_train.mesh");
	ent->setQueryFlags(1 << 0);
	ent->setCastShadows(true);	
	
	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", initPos);
	mNode->attachObject(ent);
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


