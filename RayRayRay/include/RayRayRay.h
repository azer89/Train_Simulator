/*
-----------------------------------------------------------------------------
Filename:    RayRayRay.h
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

#include "BaseApplication.h"
#include "CEGUI.h"
#include "CEGUIOgreRenderer.h"

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif


class RayRayRay : public BaseApplication
{
public:
    RayRayRay(void);
    virtual ~RayRayRay(void);

protected:
    virtual void createScene(void);
    virtual void chooseSceneManager(void);
    virtual void createFrameListener(void);

    //frame listener    
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    //mouse listener
    virtual bool mouseMoved(const OIS::MouseEvent &arg);
    virtual bool mousePressed(const OIS::MouseEvent &arg,OIS::MouseButtonID id);
    virtual bool mouseReleased(const OIS::MouseEvent &arg,OIS::MouseButtonID id);

protected:
	Ogre::RaySceneQuery *mRaySceneQuery;// The ray scene query pointer
    
	bool mLMouseDown, mRMouseDown;		// True if the mouse buttons are down
    int mCount;							// The number of robots on the screen
    
	Ogre::SceneNode *mCurrentObject;	// The newly created object
    CEGUI::Renderer *mGUIRenderer;		// CEGUI renderer
	
    float mRotateSpeed;		
};

#endif // #ifndef __RayRayRay_h_
