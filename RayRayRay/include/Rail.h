

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

class Rail
{
public:
	Rail(void);
    virtual ~Rail(void);

	Ogre::list<Ogre::Entity*>::type getRailPoints();
	Ogre::SceneNode* addPoint(Ogre::SceneManager* mSceneMgr, Ogre::Vector3 pos);
	

private:
	int num;
	Ogre::list<Ogre::Entity*>::type railPoints;
	Ogre::list<Ogre::SceneNode*>::type railNodes;
};