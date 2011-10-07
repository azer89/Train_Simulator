
#include "Stdafx.h"
#include "RayTrain.h"

//-------------------------------------------------------------------------------------
RayTrain::RayTrain(Ogre::SceneManager* mSceneMgr, Rail* rail )
{
	this->mSceneMgr = mSceneMgr;
	this->rail = rail;
}

//-------------------------------------------------------------------------------------
RayTrain::~RayTrain(void)
{
	
}