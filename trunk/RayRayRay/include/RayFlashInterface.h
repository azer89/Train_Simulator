
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
	bool isInsideMenu(int mouseX, int mouseY);

	Hikari::HikariManager* hikariMgr;
	Hikari::HikariManager* objectHikariMgr;

	Hikari::FlashControl* mainMenuControl;
	Hikari::FlashControl* objectControls;

private:
	RayRayRay* rayApp;
	bool isMenuOpen;

	Hikari::FlashValue onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onCurveChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onMenuStateChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);
	Hikari::FlashValue onNumTrainChange(Hikari::FlashControl* caller, const Hikari::Arguments& args);
};