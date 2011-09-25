

#include "Rail.h"

//-------------------------------------------------------------------------------------
Rail::Rail(void)
{
	num = 0;
}
//-------------------------------------------------------------------------------------
Rail::~Rail(void)
{
}

Ogre::list<Ogre::Entity> Rail::getRailPoints()
{
	return this->railPoints;
}

Ogre::Entity* Rail::addPoint(Ogre::SceneManager* mSceneMgr)
{
	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity("RailPoint" + num, "cube.mesh");
	this->railPoints.push_back(ent);

	this->num++;

	return ent;
}