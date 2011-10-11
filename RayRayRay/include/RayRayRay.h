/*
-----------------------------------------------------------------------------
Filename:    RayRayRay.h
Author:      Reza Adhitya Saputra
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC9 (July 2011)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/
#ifndef __RayRayRay_h_
#define __RayRayRay_h_

#include "Stdafx.h"

#include "ClassDefine.h"
#include "Rail.h"
#include "RayTrain.h"
#include "RayTerrain.h"
#include "BaseApplication.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

using namespace Ogre;

class RayRayRay : public BaseApplication
{
public:
    RayRayRay(void);			// constructor
    virtual ~RayRayRay(void);	// destructor

	RayFlashInterface* menu;	// hikari
	Ogre::Viewport* hViewPort;	// necessary for hikari
	Rail* rail;
	RayTrain* train;

	void shutdownApp(void);
	void setCurve(int num);
	void setPoleHeight(Ogre::Real h);

protected:
    virtual void createScene(void);
	virtual void destroyScene(void);
	virtual void chooseSceneManager(void);
	virtual void createFrameListener(void);
 
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& arg);
 
	// OIS::MouseListener
	virtual bool mouseMoved(const OIS::MouseEvent& arg);
	virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);

	// OIS::KeyListener
	virtual bool keyPressed(const OIS::KeyEvent& arg);
	 
	Ogre::SceneNode *mCurrentObject;	//pointer to our currently selected object
	Ogre::RaySceneQuery* mRayScnQuery;	//pointer to our ray scene query	
 
	bool bLMouseDown, bRMouseDown;		//true if mouse buttons are held down
	int mCount;							//number of objects created
	float mRotateSpeed;					//the rotation speed for the camera

	bool hideTray;						// necessary for hiding tray

private:
	
	RayTerrain* rayTerrain;			// responsible to draw tracks
    OgreBites::Label* mInfoLabel;	// message info

	void repositionObjectMenu();
};

#endif // #ifndef __RayRayRay_h_
