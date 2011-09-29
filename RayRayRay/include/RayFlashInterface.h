
#include "ClassDefine.h"
#include "Hikari.h"

#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>

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

	Hikari::HikariManager* hikariMgr;

private:
	
	Hikari::FlashControl* controls;
	RayRayRay* rayApp;

	Hikari::FlashValue onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
};