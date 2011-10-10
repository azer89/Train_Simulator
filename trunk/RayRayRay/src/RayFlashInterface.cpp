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
	mainMenuControl->callFunction("setFPS", Hikari::Args((int)mWindow->getAverageFPS()));
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::setupHikari(void)
{
	using namespace Hikari;
	
	hikariMgr = new HikariManager("..\\..\\media\\flash\\RayRayRayUI\\bin");
	
	mainMenuControl = hikariMgr->createFlashOverlay("Menu", rayApp->hViewPort, 300, 300, Position(TopLeft));
	
	mainMenuControl->load("RayRayRayUI.swf");
	mainMenuControl->setDraggable(false);
	mainMenuControl->setTransparent(true, true);

	mainMenuControl->bind("Start", FlashDelegate(this, &RayFlashInterface::onStartClick));
	mainMenuControl->bind("Stop", FlashDelegate(this, &RayFlashInterface::onStopClick));
	mainMenuControl->bind("Exit", FlashDelegate(this, &RayFlashInterface::onExitClick));
	mainMenuControl->bind("Curve", FlashDelegate(this, &RayFlashInterface::onCurveChange));
	mainMenuControl->bind("MenuState", FlashDelegate(this, &RayFlashInterface::onMenuStateChange));
	mainMenuControl->bind("NumTrain", FlashDelegate(this, &RayFlashInterface::onNumTrainChange));

	objectControls = hikariMgr->createFlashOverlay("OControl", rayApp->hViewPort, 300, 100, Position(TopLeft));

	objectControls->load("ObjectUI.swf");
	objectControls->setDraggable(false);
	objectControls->setTransparent(true, true);
	objectControls->hide();

	objectControls->bind("Height", FlashDelegate(this, &RayFlashInterface::onHeightChange));
}

void RayFlashInterface::showObjectControl(int xMPos, int yMPos, int height)
{
	using namespace Hikari;

	objectControls->callFunction("setVal", Hikari::Args(height));
	objectControls->show();
	objectControls->setPosition(Position(TopLeft, xMPos, yMPos));

	oCPos.x = xMPos;
	oCPos.y = yMPos;
}

void RayFlashInterface::hideObjectControl()
{
	objectControls->hide();
}

bool RayFlashInterface::isInsideMenu(int mouseX, int mouseY)
{
	if(isMenuOpen && 
		mouseX >= 0 && 
		mouseX <= 170 && 
		mouseY >= 0 && 
		mouseY <= 220)
	{
		return true;
	}
	else if (!isMenuOpen && 
		mouseX >= 0 && 
		mouseX <= 60 && 
		mouseY >= 0 && 
		mouseY <= 60)
	{
		return true;
	}
	else if(objectControls->getVisibility() &&
		mouseX >= oCPos.x &&
		mouseX <= (oCPos.x + 170) &&
		mouseY >= oCPos.y &&
		mouseY <= (oCPos.y + 50))
	{
		return true;
	}

	return false;
}

Hikari::FlashValue RayFlashInterface::onStartClick(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString();
	this->rayApp->train->startTrain();

	return FLASH_VOID;
}

Hikari::FlashValue RayFlashInterface::onStopClick(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString();
	this->rayApp->train->stopTrain();

	return FLASH_VOID;
}

Hikari::FlashValue RayFlashInterface::onExitClick(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	this->rayApp->shutdownApp();
	
	return FLASH_VOID;
}

Hikari::FlashValue RayFlashInterface::onCurveChange(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "bezier")
	{
		//this->rayApp->rail->setCurve(0);
		this->rayApp->setCurve(0);
	}
	else if(text == "bspline")
	{
		//this->rayApp->rail->setCurve(1);
		this->rayApp->setCurve(1);
	}
	else if(text == "linear")
	{
		//this->rayApp->rail->setCurve(2);
		this->rayApp->setCurve(2);
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

Hikari::FlashValue RayFlashInterface::onNumTrainChange(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 

	if(text == "deletetrain")
	{
		this->rayApp->train->deleteTrain();
	}
	else if(text == "addtrain")
	{
		this->rayApp->train->addTrain();
	}

	return FLASH_VOID;
}

Hikari::FlashValue RayFlashInterface::onHeightChange(Hikari::FlashControl* caller, const Hikari::Arguments& args)
{
	using namespace Hikari;
	std::string text = args.at(0).getString(); 
	Ogre::Real temp = ::atof(text.c_str());

	rayApp->setPoleHeight(temp);

	return FLASH_VOID;
}