#include "Stdafx.h"
#include "Rail.h"

//-------------------------------------------------------------------------------------
Rail::Rail(Ogre::SceneManager* mSceneMgr)
{
	this->mSceneMgr = mSceneMgr;
	this->num = 0;
	trackNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TrackCurveNode");
}
//-------------------------------------------------------------------------------------
Rail::~Rail(void)
{
}

std::vector<Ogre::Entity*> Rail::getRailPoints()
{
	return this->railPoints;
}

Ogre::SceneNode* Rail::addPoint(Ogre::Vector3 pos)
{
	char name[16];
	sprintf(name, "RailPoint%d", num++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "cube.mesh");
	ent->setQueryFlags(1 << 0);
	ent->setCastShadows(true);
	
	// std::cout << "name = " << ent->getName() << "\n"; // debug
	// std::cout << "number = " << this->num << "\n"; // debug

	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", pos);
	mNode->attachObject(ent);

	// attach to list
	
	this->railNodes.push_back(mNode);
	//this->railPoints.push_back(ent);

	//lets shrink the object, only because the terrain is pretty small
	mNode->setScale(0.03f, 0.07f, 0.03f);

	this->updateTrack();

	return mNode;
}

void Rail::updateTrack(void)
{
	for(int a = 0; a < railNodes.size(); a++)
	{	
	}
	
}