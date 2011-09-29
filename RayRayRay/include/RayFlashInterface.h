
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

	Hikari::HikariManager* hikariMgr;
	Hikari::FlashControl* controls;
	void setupHikari();
	void update(Ogre::RenderWindow* mWindow);

private:
	RayRayRay* rayApp;
	Hikari::FlashValue onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
};