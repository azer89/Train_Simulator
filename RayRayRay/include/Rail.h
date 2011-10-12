
#include "Stdafx.h"
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

	Ogre::Vector3 defScale;
	std::vector<Ogre::SceneNode*> railNodes;	// contains pole positions	
	std::vector<Ogre::Vector3> tiePoints;		// contains tie position
	
private:
	std::vector<Ogre::SceneNode*> tiesNodes;	// contains tie nodes
	std::vector<Ogre::Vector3> points;			// pole positions + control points
	std::vector<Ogre::Vector3> curvePoints;		// interpolated points

	int num;				// number of rail point
	int tieNum;				// number of tie
	bool initiated;			// is initiated
	int curveType;			// type of curve: bezier of b-spline
	Ogre::Real dist;		// for interpolation

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
	void showTie(Ogre::SceneNode* mNode, Ogre::Vector3 pos1, Ogre::Vector3 pos2);
	void hideTie(int num);
	void allocateTie(int num);
	void deleteTieCube(void);
	void buildTieCube(void);

	
};