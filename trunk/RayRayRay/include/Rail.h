

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include "DynamicLines.h"

class Rail
{
public:
	Rail(Ogre::SceneManager* mSceneMgr);
    virtual ~Rail(void);

	std::vector<Ogre::Entity*> getRailPoints();
	Ogre::SceneNode* addPoint(Ogre::Vector3 pos);
	void updateTrack(void);

private:
	int num;
	bool initiated;
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* linesNode;
	DynamicLines *lines;
	//Ogre::SimpleSpline* splineLine;
	Ogre::SceneNode* trackNode;
	std::vector<Ogre::Entity*> railPoints;
	std::vector<Ogre::SceneNode*> railNodes;
};