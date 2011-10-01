#include "Stdafx.h"
#include "Rail.h"


//-------------------------------------------------------------------------------------
Rail::Rail(Ogre::SceneManager* mSceneMgr)
{
	this->initiated = false;
	this->mSceneMgr = mSceneMgr;
	this->num = 0;

	lines = new DynamicLines(Ogre::RenderOperation::OT_LINE_LIST);
	linesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TrackLines");
	
}
//-------------------------------------------------------------------------------------
Rail::~Rail(void)
{
}

//std::vector<Ogre::Entity*> Rail::getRailPoints()
//{
//	return this->railPoints;

	
//}

Ogre::SceneNode* Rail::addPoint(Ogre::Vector3 pos)
{
	char name[16];
	sprintf(name, "RailPoint%d", num++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "cube.mesh");
	ent->setQueryFlags(1 << 0);
	ent->setCastShadows(true);
	
	// std::cout << "name = " << ent->getName() << "\n"; // debug
	// std::cout << "number = " << this->num << "\n"; // debug

	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", pos);
	mNode->attachObject(ent);

	// attach to list
	
	this->railNodes.push_back(mNode);
	//this->railPoints.push_back(ent);

	//lets shrink the object, only because the terrain is pretty small
	mNode->setScale(0.03f, 0.07f, 0.03f);

	this->updateTrack();

	return mNode;
}

void Rail::updateTrack(void)
{	
	if(railNodes.size() < 3) return; // not enough point

	lines->clear();
	this->createBezierCurve();
	
	for(int a = 0; a < curvePoints.size()-1; a++)
	{	
		Ogre::Vector3 first = curvePoints[a];
		Ogre::Vector3 second = curvePoints[a + 1];

		lines->addPoint(first.x, first.y + 10, first.z);
		lines->addPoint(second.x, second.y + 10, second.z);		
	}

	Ogre::Vector3 f = curvePoints[curvePoints.size()- 1];
	Ogre::Vector3 s = curvePoints[0];

	lines->addPoint(f.x, f.y + 10, f.z);
	lines->addPoint(s.x, s.y + 10, s.z);

	lines->update();
	
	linesNode->detachAllObjects();
	linesNode->attachObject(lines);	
}

void Rail::createBezierCurve(void)
{
	points.clear();
	curvePoints.clear();
	int cSize = railNodes.size();

	for(int a = 0; a < cSize; a++)
	{
		Ogre::Vector3 one = railNodes[(a + 0)%cSize]->getPosition();
		Ogre::Vector3 two = railNodes[(a + 1)%cSize]->getPosition();
		Ogre::Vector3 three = railNodes[(a + 2)%cSize]->getPosition();
		Ogre::Vector3 four = railNodes[(a + 3)%cSize]->getPosition();

		this->calculateControlPoints(one, two, three, four);
	}

	Ogre::Real inc = 1.0f / 100.0f;

	int size = points.size();

	for(int a = 0; a < size; a+=3)
	{		
		Ogre::Vector3 one = points[(a + 0)%size];
		Ogre::Vector3 two = points[(a + 1)%size];
		Ogre::Vector3 three = points[(a + 2)%size];
		Ogre::Vector3 four = points[(a + 3)%size];

		for(Ogre::Real t = 0.0f; t < 1.0f; t += inc)
		{
			Ogre::Real xPoint = this->getBezierPoint(one.x, two.x, three.x, four.x, t);
			Ogre::Real yPoint = this->getBezierPoint(one.y, two.y, three.y, four.y, t);
			Ogre::Real zPoint = this->getBezierPoint(one.z, two.z, three.z, four.z, t);

			Ogre::Vector3 newV = Ogre::Vector3(xPoint, yPoint, zPoint);

			curvePoints.push_back(newV);
		}
	}

}

Ogre::Real Rail::getBezierPoint(Ogre::Real p0, Ogre::Real p1, Ogre::Real p2, Ogre::Real p3, Ogre::Real t)
{
	Ogre::Real oneMinT = 1.0f - t;
	
	Ogre::Real oneMinT2 = oneMinT * oneMinT;
	Ogre::Real oneMinT3 = oneMinT2 * oneMinT;

	Ogre::Real t2 = t * t;
	Ogre::Real t3 = t2 * t;

	Ogre::Real b = (oneMinT3 * p0) + (3 * oneMinT2 * t * p1) + (3 * oneMinT * t2 * p2) + (t3 * p3); 
	
	return b;
}

void Rail::calculateControlPoints(Ogre::Vector3 v0, Ogre::Vector3 v1, Ogre::Vector3 v2, Ogre::Vector3 v3)
{	
	Ogre::Vector3 c1, c2, c3;

	c1.x = (v0.x + v1.x) / 2.0f;
	c1.y = (v0.y + v1.y) / 2.0f;
	c1.z = (v0.z + v1.z) / 2.0f;
	c2.x = (v1.x + v2.x) / 2.0f;
	c2.y = (v1.y + v2.y) / 2.0f;
	c2.z = (v1.z + v2.z) / 2.0f;
	c3.x = (v2.x + v3.x) / 2.0f;
	c3.y = (v2.y + v3.y) / 2.0f;
	c3.z = (v2.z + v3.z) / 2.0f;

	Ogre::Real len1 = v0.distance(v1);
	Ogre::Real len2 = v1.distance(v2);
	Ogre::Real len3 = v2.distance(v3);

	Ogre::Real k1 = len1 / (len1 + len2);
	Ogre::Real k2 = len2 / (len2 + len3);

	Ogre::Vector3 m1, m2;
	m1.x = c1.x + (c2.x - c1.x) * k1;
	m1.y = c1.y + (c2.y - c1.y) * k1;
	m1.z = c1.z + (c2.z - c1.z) * k1;

	m2.x = c2.x + (c3.x - c2.x) * k2;
	m2.y = c2.y + (c3.y - c2.y) * k2;
	m2.z = c2.z + (c3.z - c2.z) * k2;

	Ogre::Vector3 ctrl1, ctrl2;

	ctrl1.x = m1.x + (c2.x - m1.x) * 0.5f + v1.x - m1.x;
	ctrl1.y = m1.y + (c2.y - m1.y) * 0.5f + v1.y - m1.y;
	ctrl1.z = m1.z + (c2.z - m1.z) * 0.5f + v1.z - m1.z;

	ctrl2.x = m2.x + (c2.x - m2.x) * 0.5f + v2.x - m2.x;
	ctrl2.y = m2.y + (c2.y - m2.y) * 0.5f + v2.y - m2.y;
	ctrl2.z = m2.z + (c2.z - m2.z) * 0.5f + v2.z - m2.z;

	points.push_back(v1);
	points.push_back(ctrl1);
	points.push_back(ctrl2);
}