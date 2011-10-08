
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

#include "ClassDefine.h"
#include "DynamicLines.h"

class Rail
{
public:
	Rail(Ogre::SceneManager* mSceneMgr, Ogre::Terrain* pTerrain);
    virtual ~Rail(void);

	Ogre::SceneNode* addPoint(Ogre::Vector3 pos);
	void deleteRailPoint(std::string name);
	void updateTrack(void);
	void setCurve(int num);

	std::vector<Ogre::SceneNode*> railNodes;	// contains pole positions
	//std::vector<Ogre::SceneNode*> tiesNodes;	// contains tie nodes
	std::vector<Ogre::Vector3> tiePoints;		// contains tie position
	std::vector<Ogre::Vector3> points;			// pole positions + control points
	std::vector<Ogre::Vector3> curvePoints;		// interpolated points
	
private:
	int num;			// number of rail point
	int tieNum;			// number of tie
	bool initiated;		// is initiated
	int curveType;		// type of curve: bezier of b-spline

	Ogre::Entity* tieEntity;			// tie entity
	Ogre::SceneManager* mSceneMgr;		// scene manager
	Ogre::Terrain* pTerrain;			// terrain, for calculate height
	Ogre::SceneNode* linesNode;			// node of lines
	DynamicLines *lines;				// dynamic lines
	Ogre::SceneNode* trackNode;			// for track node
	
	Ogre::Real getBezierPoint(Ogre::Real p0, Ogre::Real p1, Ogre::Real p2, Ogre::Real p3, Ogre::Real t);
	Ogre::Real getHeight(Ogre::Vector3 vect);
	void createBezierCurve(void);
	void createBSplineCurve(void);
	void createLinearCurve(void);
	void calculateControlPoints(Ogre::Vector3 v0, Ogre::Vector3 v1, Ogre::Vector3 v2, Ogre::Vector3 v3, Ogre::Real weight);
	void addTie(Ogre::Vector3 pos, Ogre::Quaternion rot);
	void deleteTieCube(void);
	void initTieCube(void);
	
};