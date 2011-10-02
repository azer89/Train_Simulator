#include "Stdafx.h"
#include "Rail.h"


//-------------------------------------------------------------------------------------
Rail::Rail(Ogre::SceneManager* mSceneMgr, Ogre::Terrain* pTerrain): initiated(false), num(0)
{
	this->mSceneMgr = mSceneMgr;
	this->pTerrain = pTerrain;

	lines = new DynamicLines(Ogre::RenderOperation::OT_LINE_LIST);
	linesNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("TrackLines");
	
}
//-------------------------------------------------------------------------------------
Rail::~Rail(void)
{
}

void Rail::deleteRailPoint(std::string name)
{
	for(int a = 0; a < railNodes.size(); a++)
	{
		if(railNodes[a]->getName() == name)
		{
			this->mSceneMgr->getRootSceneNode()->removeChild(name);
			railNodes.erase(railNodes.begin() + a);
			this->updateTrack();
		}
	}
}

Ogre::SceneNode* Rail::addPoint(Ogre::Vector3 pos)
{
	char name[16];
	sprintf(name, "RailPoint%d", num++);

	Ogre::Entity* ent;
	ent = mSceneMgr->createEntity(name, "cube.mesh");
	ent->setQueryFlags(1 << 0);
	ent->setCastShadows(true);


	// attach the object to a scene node
	Ogre::SceneNode* mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", pos);
	mNode->attachObject(ent);

	// attach to list	
	this->railNodes.push_back(mNode);

	//lets shrink the object, only because the terrain is pretty small
	mNode->setScale(0.03f, 0.07f, 0.03f);

	this->updateTrack();

	return mNode;
}

void Rail::updateTrack(void)
{	
	lines->clear();

	if(railNodes.size() < 3) 
	{	
		lines->update();
		return; // not enough point
	}

	this->createBezierCurve();
	
	/*
	for(int a = 0; a < curvePoints.size()-1; a++)
	{	
		Ogre::Vector3 first = curvePoints[a];
		Ogre::Vector3 second = curvePoints[a + 1];

		lines->addPoint(first.x, first.y + 10, first.z);
		lines->addPoint(second.x, second.y + 10, second.z);		
	}
	*/

	Ogre::Vector3 f = curvePoints[curvePoints.size()- 1];
	Ogre::Vector3 s = curvePoints[0];

	lines->addPoint(f.x, f.y + 10, f.z);
	lines->addPoint(s.x, s.y + 10, s.z);

	std::vector<Ogre::Vector3> rPoints;
	std::vector<Ogre::Vector3> lPoints;
	
	for(int a = 0; a < tiesPoints.size()-1; a++)
	{
		Ogre::Vector3 f = tiesPoints[a];
		Ogre::Vector3 s = tiesPoints[a + 1];
		
		Ogre::Real prefRatio = 2.0f / f.distance(s);
		Ogre::Vector3 vect = (s - f) * prefRatio;

		Ogre::Vector3 rv = Ogre::Quaternion(Ogre::Degree(90), Ogre::Vector3::UNIT_Y) * vect;
		Ogre::Vector3 lv = Ogre::Quaternion(Ogre::Degree(-90), Ogre::Vector3::UNIT_Y) * vect;

		rv += f;
		lv += f;

		rPoints.push_back(rv);
		lPoints.push_back(lv);

		lines->addPoint(rv.x, rv.y + 10, rv.z);
		lines->addPoint(lv.x, lv.y + 10, lv.z);
	}

	int parSize = rPoints.size();
	for(int a = 0; a < parSize; a++)
	{
		Ogre::Vector3 fr = rPoints[a%parSize];
		Ogre::Vector3 sr = rPoints[(a + 1)%parSize];
		Ogre::Vector3 fl = lPoints[a%parSize];
		Ogre::Vector3 sl = lPoints[(a + 1)%parSize];

		lines->addPoint(fr.x, fr.y + 10, fr.z);
		lines->addPoint(sr.x, sr.y + 10, sr.z);

		lines->addPoint(fl.x, fl.y + 10, fl.z);
		lines->addPoint(sl.x, sl.y + 10, sl.z);
	}
	

	lines->update();
	
	linesNode->detachAllObjects();
	linesNode->attachObject(lines);	
}

void Rail::createBezierCurve(void)
{
	points.clear();
	curvePoints.clear();
	tiesPoints.clear();

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

			curvePoints.push_back(Ogre::Vector3(newV.x, getHeight(newV), newV.z));
		}

		Ogre::Real dist = 0.5f / one.distance(two);
		
		for(Ogre::Real t = 0.0f; t < 1.0f; t += dist)
		{
			Ogre::Real xPoint = this->getBezierPoint(one.x, two.x, three.x, four.x, t);
			Ogre::Real yPoint = this->getBezierPoint(one.y, two.y, three.y, four.y, t);
			Ogre::Real zPoint = this->getBezierPoint(one.z, two.z, three.z, four.z, t);

			Ogre::Vector3 newV = Ogre::Vector3(xPoint, yPoint, zPoint);
			tiesPoints.push_back(Ogre::Vector3(newV.x, getHeight(newV), newV.z));
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

	Ogre::Vector3 ctrl1 = m1 + (c2 - m1) * 0.5f + v1 - m1;
	Ogre::Vector3 ctrl2 = m2 + (c2 - m2) * 0.5f + v2 - m2;

	points.push_back(Ogre::Vector3(v1.x, getHeight(v1), v1.z));
	points.push_back(Ogre::Vector3(ctrl1.x, getHeight(ctrl1), ctrl1.z));
	points.push_back(Ogre::Vector3(ctrl2.x, getHeight(ctrl2), ctrl2.z));
}


Ogre::Real Rail::getHeight(Ogre::Vector3 vect)
{
	
	Ogre::Ray mouseRay(Ogre::Vector3(vect.x, 5000.0f, vect.z), Ogre::Vector3::NEGATIVE_UNIT_Y);
	std::pair <bool, Ogre::Vector3> test;
	test = pTerrain->rayIntersects(mouseRay, true, 0);

	if (test.first) 
	{
		Ogre::Real terrainHeight = test.second.y;

		if(terrainHeight <= vect.y) return vect.y;
		
		return terrainHeight;
	}
	
	return 0.0f;

}
