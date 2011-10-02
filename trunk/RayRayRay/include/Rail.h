

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

	//std::vector<Ogre::Entity*> getRailPoints();
	Ogre::SceneNode* addPoint(Ogre::Vector3 pos);
	void updateTrack(void);

private:
	int num;
	bool initiated;
	//Ogre::Real tiesDist;
	std::vector<Ogre::Vector3> tiesPoints;

	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* linesNode;
	DynamicLines *lines;
	Ogre::SceneNode* trackNode;
	//std::vector<Ogre::Entity*> railPoints;
	std::vector<Ogre::SceneNode*> railNodes;
	std::vector<Ogre::Vector3> points;
	std::vector<Ogre::Vector3> curvePoints;

	void createBezierCurve(void);
	Ogre::Real getBezierPoint(Ogre::Real p0, Ogre::Real p1, Ogre::Real p2, Ogre::Real p3, Ogre::Real t);
	void calculateControlPoints(Ogre::Vector3 v0, Ogre::Vector3 v1, Ogre::Vector3 v2, Ogre::Vector3 v3);
};