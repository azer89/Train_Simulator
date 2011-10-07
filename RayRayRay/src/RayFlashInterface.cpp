#include "Stdafx.h"

#include "RayFlashInterface.h"
#include "RayRayRay.h"
#include "FlashValue.h"

//-------------------------------------------------------------------------------------
RayFlashInterface::~RayFlashInterface(void)
{
	isMenuOpen = false;
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::update(Ogre::RenderWindow* mWindow)
{
	hikariMgr->update();
	
	controls->callFunction("setFPS", Hikari::Args((int)mWindow->getAverageFPS()));	
	//std::cout << (int)mWindow->getAverageFPS() << "\n";
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::setupHikari(void)
{
	using namespace Hikari;
	
	hikariMgr = new HikariManager("..\\..\\media\\flash\\RayRayRayUI\\bin");
	//objectHikariMgr = new HikariManager("..\\..\\media\\flash\\ObjectUI\\bin");
	
	controls = hikariMgr->createFlashOverlay("Menu", rayApp->hViewPort, 300, 300, Position(TopLeft));
	controls->load("RayRayRayUI.swf");
	controls->setDraggable(false);
	controls->setTransparent(true, true);
	controls->bind("Start", FlashDelegate(this, &RayFlashInterface::onStartClick));
	controls->bind("Stop", FlashDelegate(this, &RayFlashInterface::onStopClick));
	controls->bind("Exit", FlashDelegate(this, &RayFlashInterface::onExitClick));
	controls->bind("Curve", FlashDelegate(this, &RayFlashInterface::onCurveChange));
	controls->bind("MenuState", FlashDelegate(this, &RayFlashInterface::onMenuStateChange));
	
}

void RayFlashInterface::showObjectControl(int xMPos, int yMPos)
{
	/*
	using namespace Hikari;
	//if(this->objectControls) delete objectControls;

	objectControls = objectHikariMgr->createFlashOverlay("ObjectMenu", rayApp->hViewPort, xMPos, yMPos, Position(TopLeft));
	objectControls->load("ObjectUI.swf");
	objectControls->setDraggable(false);
	objectControls->setTransparent(true, true);
	*/
}

bool RayFlashInterface::isInsideMenu(int mouseX, int mouseY)
{
	if(isMenuOpen && mouseX >= 0 && mouseX <= 170 && mouseY >= 0 && mouseY <= 220)
	{
		return true;
	}
	else if (!isMenuOpen && mouseX >= 0 && mouseX <= 60 && mouseY >= 0 && mouseY <= 60)
	{
		return true;
	}

	return false;
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

Hikari::FlashValue RayFlashInterface::onCurveChange(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "bezier")
	{
		this->rayApp->rail->setCurve(0);
	}
	else if(text == "bspline")
	{
		this->rayApp->rail->setCurve(1);
	}
	else if(text == "linear")
	{
		this->rayApp->rail->setCurve(2);
	}
	
	return FLASH_VOID;
}

Hikari::FlashValue RayFlashInterface::onMenuStateChange(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "open")
	{
		isMenuOpen = true;
	}
	else if(text == "close")
	{
		isMenuOpen = false;
	}

	return FLASH_VOID;
}