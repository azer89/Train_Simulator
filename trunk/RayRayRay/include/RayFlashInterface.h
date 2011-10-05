
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
	void showObjectControl(int xMPos, int yMPos);

	Hikari::HikariManager* hikariMgr;
	Hikari::HikariManager* objectHikariMgr;

private:
	
	Hikari::FlashControl* controls;
	Hikari::FlashControl* objectControls;
	RayRayRay* rayApp;

	Hikari::FlashValue onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
};