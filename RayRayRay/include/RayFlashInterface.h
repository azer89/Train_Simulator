
#ifndef __RayFlashInterface__
#define __RayFlashInterface__

#include "Stdafx.h"
#include "ClassDefine.h"
#include "Hikari.h"

class RayFlashInterface
{

public:
	RayFlashInterface(RayRayRay* rayApp):hikariMgr(0)
	{
		this->rayApp = rayApp;
	}
    virtual ~RayFlashInterface(void);
	
	void setupHikari();
	void update(Ogre::RenderWindow* mWindow);
	void showObjectControl(int xMPos, int yMPos, int height);
	void hideObjectControl();
	bool isInsideMenu(int mouseX, int mouseY);

	Hikari::HikariManager* hikariMgr;
	Hikari::HikariManager* objectHikariMgr;

private:

	Hikari::FlashControl* mainMenuControl;
	Hikari::FlashControl* objectControls;

	RayRayRay* rayApp;
	bool isMenuOpen;
	Ogre::Vector2 oCPos;

	Hikari::FlashValue onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to startthe train
	Hikari::FlashValue onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to stop the train
	Hikari::FlashValue onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to close app
	Hikari::FlashValue onCurveChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to change curve type
	Hikari::FlashValue onMenuStateChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);	// event listener when menu opened/closed
	Hikari::FlashValue onNumTrainChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);	// event listener to change number of train

	Hikari::FlashValue onHeightChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);		// event listener to change pole's height
};

#endif