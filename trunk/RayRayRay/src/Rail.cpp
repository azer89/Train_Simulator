
#include "Stdafx.h"
#include "Rail.h"

//-------------------------------------------------------------------------------------
// Constructor
Rail::Rail(Ogre::SceneManager* mSceneMgr, Ogre::Terrain* pTerrain): 
	initiated(false), 
	num(0), 
	tieNum(0),
	curveType(0),
	dist(5.0f)
{
	this->mSceneMgr = mSceneMgr;
	this->pTerrain = pTerrain;
	this->defScale = Ogre::Vector3(5.0f, 8.0f, 5.0f);

	lines = new DynamicLines(Ogre::RenderOperation::OT_LINE_LIST);
	linesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TrackLines");
}

//-------------------------------------------------------------------------------------
// Destructor 
Rail::~Rail(void)
{
	if(lines) delete lines;
}

//-------------------------------------------------------------------------------------
// Delete pole
void Rail::deleteRailPoint(std::string name)
{
	int rSize = railNodes.size();
	if(rSize == 3) return; // prevent to delete

	for(int a = 0; a < rSize; a++)
	{
		if(railNodes[a]->getName() == name)
		{
			this->mSceneMgr->getRootSceneNode()->removeChild(name);
			railNodes.erase(railNodes.begin() + a);
			this->updateTrack();
			return;
		}
	}
}

//-------------------------------------------------------------------------------------
// Add pole
Ogre::SceneNode* Rail::addPoint(Ogre::Vector3 pos)
{
	char name[16];
	sprintf(name, "RailPoint%d", num++);
	
	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "pillar.mesh");
	//ent->setMaterialName("woodmat");
	ent->setQueryFlags(1 << 0);
	ent->setCastShadows(true);	

	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", pos);
	mNode->attachObject(ent);

	
	this->railNodes.push_back(mNode);		// attach to list		
	mNode->setScale(defScale);				//lets shrink the object

	this->updateTrack();

	return mNode;
}

//-------------------------------------------------------------------------------------
// update track if user change the pole
void Rail::updateTrack(void)
{	
	lines->clear();
	deleteTieCube();

	if(railNodes.size() < 3) 
	{	
		lines->update();
		return;
	}
	
	points.clear();
	curvePoints.clear();
	tiePoints.clear();

	if(curveType == 0) this->createBezierCurve();
	else if (curveType == 1) this->createBSplineCurve();
	else if (curveType == 2) this->createLinearCurve();
	
	/*
	for(int a = 0; a < curvePoints.size()-1; a++)
	{	
		Ogre::Vector3 first = curvePoints[a];
		Ogre::Vector3 second = curvePoints[a + 1];

		lines->addPoint(first.x, first.y, first.z);
		lines->addPoint(second.x, second.y, second.z);		
	}
	*/

	Ogre::Vector3 f = curvePoints[curvePoints.size() - 1];
	Ogre::Vector3 s = curvePoints[0];

	std::vector<Ogre::Vector3> rPoints;
	std::vector<Ogre::Vector3> lPoints;
	
	int cSize = curvePoints.size();
	Ogre::Real gap = 2.0f;
	Ogre::Real count = 0.0f;

	for(int a = 0; a < cSize; a++)
	{
		Ogre::Vector3 f = curvePoints[a];
		Ogre::Vector3 s = curvePoints[(a + 1) % cSize];
		count += f.distance(s);

		if(count >= gap)
		{
			Ogre::Real prefRatio = 2.0f / f.distance(s);
			Ogre::Vector3 vect = (s - f) * prefRatio;

			Ogre::Vector3 rv = Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y) * vect;
			Ogre::Vector3 lv = Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_Y) * vect;

			rv += f;
			lv += f;
			
			this->tiePoints.push_back(f);
			
			rPoints.push_back(rv);
			lPoints.push_back(lv);
			
			lines->addPoint(rv.x, rv.y, rv.z);
			lines->addPoint(lv.x, lv.y, lv.z);

			count = 0.0f;
		}
	}

	int parSize = rPoints.size();
	for(int a = 0; a < parSize; a++)
	{
		Ogre::Vector3 fr = rPoints[a%parSize];
		Ogre::Vector3 sr = rPoints[(a + 1)%parSize];
		Ogre::Vector3 fl = lPoints[a%parSize];
		Ogre::Vector3 sl = lPoints[(a + 1)%parSize];

		lines->addPoint(fr.x, fr.y, fr.z);
		lines->addPoint(sr.x, sr.y, sr.z);

		lines->addPoint(fl.x, fl.y, fl.z);
		lines->addPoint(sl.x, sl.y, sl.z);
	}	

	lines->update();
	
	linesNode->detachAllObjects();
	linesNode->attachObject(lines);	
}

//-------------------------------------------------------------------------------------
// Set curve interpolation type
void Rail::setCurve(int num)
{
	if(num == curveType) return;

	curveType = num;
	this->updateTrack();
}

//-------------------------------------------------------------------------------------
// Main function for Linear Interpolation, nothing special
void Rail::createLinearCurve(void)
{
	int cSize = railNodes.size();
	Ogre::Vector3 yAdd = Ogre::Vector3(0, 30, 0);

	for(int a = 0; a < cSize; a++)
	{
		Ogre::Vector3 one = railNodes[a]->getPosition() + yAdd + Ogre::Vector3(0, (railNodes[a]->getScale().y - defScale.y), 0);
		Ogre::Vector3 two = railNodes[(a + 1)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, (railNodes[(a + 1)%cSize]->getScale().y - defScale.y), 0);
		Ogre::Vector3 three = railNodes[(a + 2)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, (railNodes[(a + 2)%cSize]->getScale().y - defScale.y), 0);
		Ogre::Vector3 four = railNodes[(a + 3)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, (railNodes[(a + 3)%cSize]->getScale().y - defScale.y), 0);

		this->calculateControlPoints(one, two, three, four, 0.05f);
	}
	
	int size = points.size();
	Ogre::Real oinc = 1.0f / dist;

	for(int a = 0; a < size; a++)
	{		
		Ogre::Vector3 vect01 = points[a];
		Ogre::Vector3 vect02 = points[(a + 1)%size];
		
		Ogre::Real inc = oinc / vect01.distance(vect02);

		for(Ogre::Real t = 0.0f; t < 1.0f; t += inc)
		{	
			Ogre::Vector3 vect03 = vect01 + (vect02 - vect01) * t;
			curvePoints.push_back(Ogre::Vector3(vect03.x, getHeight(vect03), vect03.z));
		}
	}
}

//-------------------------------------------------------------------------------------
// // Main function for Cubic Bezier Interpolation
void Rail::createBezierCurve(void)
{
	int cSize = railNodes.size();
	Ogre::Vector3 yAdd = Ogre::Vector3(0, 30, 0);

	for(int a = 0; a < cSize; a++)
	{
		Ogre::Vector3 one = railNodes[a]->getPosition() + yAdd + Ogre::Vector3(0, 3.6f * (railNodes[a]->getScale().y - defScale.y), 0);
		Ogre::Vector3 two = railNodes[(a + 1)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, 3.6f * (railNodes[(a + 1)%cSize]->getScale().y - defScale.y), 0);
		Ogre::Vector3 three = railNodes[(a + 2)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, 3.6f * (railNodes[(a + 2)%cSize]->getScale().y - defScale.y), 0);
		Ogre::Vector3 four = railNodes[(a + 3)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, 3.6f * (railNodes[(a + 3)%cSize]->getScale().y - defScale.y), 0);

		this->calculateControlPoints(one, two, three, four, 0.9f);
	}
	
	int size = points.size();
	Ogre::Real oinc = 1.0f / dist;

	for(int a = 0; a < size; a+=3)
	{		
		Ogre::Vector3 one = points[a];
		Ogre::Vector3 two = points[(a + 1)%size];
		Ogre::Vector3 three = points[(a + 2)%size];
		Ogre::Vector3 four = points[(a + 3)%size];

		Ogre::Real inc = oinc / two.distance(three);

		for(Ogre::Real t = 0.0f; t < 1.0f; t += inc)
		{
			Ogre::Real xPoint = this->getBezierPoint(one.x, two.x, three.x, four.x, t);
			Ogre::Real yPoint = this->getBezierPoint(one.y, two.y, three.y, four.y, t);
			Ogre::Real zPoint = this->getBezierPoint(one.z, two.z, three.z, four.z, t);

			Ogre::Vector3 newV = Ogre::Vector3(xPoint, yPoint, zPoint);
			curvePoints.push_back(Ogre::Vector3(newV.x, getHeight(newV), newV.z));
		}
	}
}

//-------------------------------------------------------------------------------------
// Main function for Cubic B-Spline Interpolation
void Rail::createBSplineCurve(void)
{
	int cSize = railNodes.size();
	Ogre::Vector3 yAdd = Ogre::Vector3(0, 30, 0);

	Ogre::Real oinc = 1.0f / dist;

	for(int a = 0; a < cSize; a++)
	{
		Ogre::Vector3 one = railNodes[a]->getPosition() + yAdd + Ogre::Vector3(0, 5.0f * (railNodes[a]->getScale().y - defScale.y), 0);
		Ogre::Vector3 two = railNodes[(a + 1)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, 5.0f * (railNodes[(a + 1)%cSize]->getScale().y - defScale.y), 0);
		Ogre::Vector3 three = railNodes[(a + 2)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, 5.0f * (railNodes[(a + 2)%cSize]->getScale().y - defScale.y), 0);
		Ogre::Vector3 four = railNodes[(a + 3)%cSize]->getPosition() + yAdd + Ogre::Vector3(0, 5.0f * (railNodes[(a + 3)%cSize]->getScale().y - defScale.y), 0);

		Ogre::Real inc = oinc / two.distance(three);

		for(Ogre::Real t = 0.0f; t < 1.0f; t += inc)
		{
			Ogre::Real it = 1.0f - t;
			Ogre::Real t2 = t*t;
			Ogre::Real t3 = t2*t;

			Ogre::Real b0 = it*it*it / 6.0f;
			Ogre::Real b1 = (3*t3 - 6*t2 + 4) / 6.0f;
			Ogre::Real b2 = (-3*t3 +3*t2 + 3*t + 1) / 6.0f;
			Ogre::Real b3 =  t3 / 6.0f;

			Ogre::Real x = (b0 * one.x) + (b1 * two.x) + (b2 * three.x) + (b3 * four.x);
			Ogre::Real y = (b0 * one.y) + (b1 * two.y) + (b2 * three.y) + (b3 * four.y);
			Ogre::Real z = (b0 * one.z) + (b1 * two.z) + (b2 * three.z) + (b3 * four.z);

			Ogre::Vector3 newV = Ogre::Vector3(x, y, z);
			curvePoints.push_back(Ogre::Vector3(newV.x, getHeight(newV), newV.z));
		}
	}
}

//-------------------------------------------------------------------------------------
// Implementation of bezier formula
Ogre::Real Rail::getBezierPoint(Ogre::Real p0, 
								Ogre::Real p1, 
								Ogre::Real p2, 
								Ogre::Real p3, 
								Ogre::Real t)
{
	Ogre::Real oneMinT = 1.0f - t;
	
	Ogre::Real oneMinT2 = oneMinT * oneMinT;
	Ogre::Real oneMinT3 = oneMinT2 * oneMinT;

	Ogre::Real t2 = t * t;
	Ogre::Real t3 = t2 * t;

	Ogre::Real b = (oneMinT3 * p0) + (3 * oneMinT2 * t * p1) + (3 * oneMinT * t2 * p2) + (t3 * p3); 
	
	return b;
}

//-------------------------------------------------------------------------------------
// Function to add additional control points, necessary for bezier interpolation
void Rail::calculateControlPoints(Ogre::Vector3 v0, 
								  Ogre::Vector3 v1, 
								  Ogre::Vector3 v2, 
								  Ogre::Vector3 v3, 
								  Ogre::Real weight)
{		
	Ogre::Vector3 c1 = (v0 + v1) / 2.0f;
	Ogre::Vector3 c2 = (v1 + v2) / 2.0f;
	Ogre::Vector3 c3 = (v2 + v3) / 2.0f;
	
	Ogre::Real len1 = v0.distance(v1);
	Ogre::Real len2 = v1.distance(v2);
	Ogre::Real len3 = v2.distance(v3);

	Ogre::Real k1 = len1 / (len1 + len2);
	Ogre::Real k2 = len2 / (len2 + len3);

	Ogre::Vector3 m1 = c1 + (c2 - c1) * k1;
	Ogre::Vector3 m2 = c2 + (c3 - c2) * k2;

	Ogre::Vector3 ctrl1 = m1 + (c2 - m1) * weight + v1 - m1;
	Ogre::Vector3 ctrl2 = m2 + (c2 - m2) * weight + v2 - m2;

	points.push_back(Ogre::Vector3(v1.x, getHeight(v1), v1.z));
	points.push_back(Ogre::Vector3(ctrl1.x, getHeight(ctrl1), ctrl1.z));
	points.push_back(Ogre::Vector3(ctrl2.x, getHeight(ctrl2), ctrl2.z));
}

//-------------------------------------------------------------------------------------
// Function to get terrain height at a point vect
Ogre::Real Rail::getHeight(Ogre::Vector3 vect)
{	
	Ogre::Ray mouseRay(Ogre::Vector3(vect.x, 5000.0f, vect.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
	std::pair <bool, Ogre::Vector3> test;
	test = pTerrain->rayIntersects(mouseRay, true, 0);

	if (test.first) 
	{
		Ogre::Real terrainHeight = test.second.y + 5.0f;
		if(terrainHeight <= vect.y) return vect.y;		
		return terrainHeight;
	}
	
	return 0.0f;
}

//-------------------------------------------------------------------------------------
// Function to add tie
void Rail::addTie(Ogre::Vector3 pos, Ogre::Quaternion rot)
{
	/*
	char name[20];
	sprintf(name, "TiesPoint%d", tieNum);
	tieNum++;

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "cube.mesh");
	ent->setCastShadows(true);	

	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node");
	mNode->attachObject(ent);

	// attach to list	
	this->tiesNodes.push_back(mNode);
	std::cout << rot << "\n";	
	
	mNode->setScale(500.002f, 0.002f, 0.002f);
	mNode->rotate(rot * Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Z));
	*/
	//mNode->rotate(Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_X));	
	//mNode->translate(pos + Ogre::Vector3(0, 10, 0));	
}

//-------------------------------------------------------------------------------------
void Rail::deleteTieCube()
{
	/*
	for(int a = tiesNodes.size() - 1; a >= 0; a--)
	{
		this->mSceneMgr->getRootSceneNode()->removeAndDestroyChild(tiesNodes[a]->getName());
		tiesNodes.erase(tiesNodes.begin() + a);
	}
	*/
}
