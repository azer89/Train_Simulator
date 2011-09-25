

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

	Ogre::list<Ogre::Entity> getRailPoints();
	Ogre::Entity* addPoint(Ogre::SceneManager* mSceneMgr);
	int num;

private:
	Ogre::list<Ogre::Entity*>::type railPoints;
};