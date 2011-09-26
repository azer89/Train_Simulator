

#include "Rail.h"

//-------------------------------------------------------------------------------------
Rail::Rail(void)
{
	this->num = 0;
	//num = OGRE_NEW Ogre::int32();
}
//-------------------------------------------------------------------------------------
Rail::~Rail(void)
{
}

Ogre::list<Ogre::Entity*>::type Rail::getRailPoints()
{
	return this->railPoints;
}

Ogre::SceneNode* Rail::addPoint(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos)
{
	char name[16];
	sprintf(name, "RailPoint%d", num++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "cube.mesh");
	this->railPoints.push_back(ent);

	std::cout << "name = " << ent->getName() << "\n"; // debug
	std::cout << "number = " << this->num << "\n"; // debug

	//attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", pos);
	mNode->attachObject(ent);

	//lets shrink the object, only because the terrain is pretty small
	mNode->setScale(0.03f, 0.07f, 0.03f);

	return mNode;
}