
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

	this->timeSinceLastFrame += timeSinceLastFrame;
	if(this->timeSinceLastFrame >= 0.02f)
	{
		this->timeSinceLastFrame = 0.0f;
		
		for(int a = 0; a < trainNodes.size(); a++)
		{
			int cSize = rail->curvePoints.size();
			if(counterPoint >= cSize) counterPoint = 0;
			
			Ogre::Vector3 v01 = rail->curvePoints[counterPoint];
			Ogre::Vector3 v02 = rail->curvePoints[(counterPoint + 1) % cSize];
			Ogre::Vector3 v03 = (v02 - v01);
			v03.normalise();
			trainNodes[a]->setDirection(v03, SceneNode::TS_PARENT);
			//Ogre::Quaternion q01 = v01.getRotationTo(v02);
			//Ogre::Quaternion q01 = Ogre::Vector3::ZERO.getRotationTo(v03);
			
			//Ogre::Radian r1 = q01.getYaw();
			//Ogre::Radian r0 = trainNodes[a]->getOrientation().getYaw();
			//trainNodes[a]->yaw(-r0);
			//trainNodes[a]->yaw(r1);
			trainNodes[a]->setPosition(v01);
			counterPoint += 2;
		}
	}
}

//-------------------------------------------------------------------------------------
void RayTrain::initTrain()
{
	this->isInitialized = true;
	Ogre::Vector3 initPos = rail->curvePoints[counterPoint];
	
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

}

//-------------------------------------------------------------------------------------
void RayTrain::stopTrain()
{

}


