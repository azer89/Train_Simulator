
#ifndef __RailTriangle__
#define __RailTriangle__

#include "Stdafx.h"

class RailTriangle
{
public:
	RailTriangle(Ogre::SceneManager* mSceneMgr)
	{
		this->mSceneMgr = mSceneMgr;
	}
	virtual ~RailTriangle(void);

	void addTriangleStrip(std::vector<Ogre::Vector3> rPoints, std::vector<Ogre::Vector3> lPoints);

private:
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* tNode;
};

#endif
