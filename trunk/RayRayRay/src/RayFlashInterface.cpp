#include "Stdafx.h"

#include "RayFlashInterface.h"
#include "RayRayRay.h"
#include "FlashValue.h"

//-------------------------------------------------------------------------------------
RayFlashInterface::~RayFlashInterface(void)
{
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::update(Ogre::RenderWindow* mWindow)
{
	hikariMgr->update();
	
	//const Ogre::RenderTarget::FrameStats& stats =  mWindow->getAverageFPS();
	//controls->callFunction("setFPS", Args((int)stats.lastFPS));

	//std::cout << (int)mWindow->getAverageFPS() << "\n";
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::setupHikari(void)
{
	using namespace Hikari;
	
	hikariMgr = new HikariManager("..\\..\\media\\flash\\RayRayRayUI\\bin");
	
	controls = hikariMgr->createFlashOverlay("Menu", rayApp->hViewPort, 300, 300, Position(TopLeft));
	controls->load("RayRayRayUI.swf");
	controls->setDraggable(false);
	controls->setTransparent(true, true);

	controls->bind("Start", FlashDelegate(this, &RayFlashInterface::onStartClick));
	controls->bind("Stop", FlashDelegate(this, &RayFlashInterface::onStopClick));
	controls->bind("Exit", FlashDelegate(this, &RayFlashInterface::onExitClick));
	
}

Hikari::FlashValue RayFlashInterface::onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	std::cout << "start" << "\n";
	
	return FLASH_VOID;
}

Hikari::FlashValue RayFlashInterface::onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 
	
	std::cout << "stop" << "\n";

	return FLASH_VOID;
}

Hikari::FlashValue RayFlashInterface::onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	std::cout << "exit" << "\n";
	
	return FLASH_VOID;
}