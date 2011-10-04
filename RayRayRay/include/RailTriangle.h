

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>

class RailTriangle
{
public:
	RailTriangle(Ogre::SceneManager* mSceneMgr);
	virtual ~RailTriangle(void);

	void addTriangleStrip(std::vector<Ogre::Vector3> rPoints, std::vector<Ogre::Vector3> lPoints);

private:
	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* tNode;
};