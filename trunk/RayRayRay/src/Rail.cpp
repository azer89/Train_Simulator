#include "Stdafx.h"
#include "Rail.h"


//-------------------------------------------------------------------------------------
Rail::Rail(Ogre::SceneManager* mSceneMgr)
{
	this->initiated = false;
	this->mSceneMgr = mSceneMgr;
	this->num = 0;

	lines = new DynamicLines(Ogre::RenderOperation::OT_LINE_LIST);
	linesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TrackLines");
	
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
	if(railNodes.size() < 2) return; // not enough point

	lines->clear();

	for(int a = 0; a < railNodes.size()-1; a++)
	{	
		Ogre::Vector3 first = railNodes[a]->getPosition();
		Ogre::Vector3 second = railNodes[a + 1]->getPosition();

		lines->addPoint(first.x, first.y + 10, first.z);
		lines->addPoint(second.x, second.y + 10, second.z);		
	}

	Ogre::Vector3 f = railNodes[railNodes.size()- 1]->getPosition();
	Ogre::Vector3 s = railNodes[0]->getPosition();

	lines->addPoint(f.x, f.y + 10, f.z);
	lines->addPoint(s.x, s.y + 10, s.z);	
	
	lines->update();
	
	linesNode->detachAllObjects();
	linesNode->attachObject(lines);
	
}