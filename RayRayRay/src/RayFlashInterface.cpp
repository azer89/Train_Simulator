

#include "RayFlashInterface.h"
#include "RayRayRay.h"

//-------------------------------------------------------------------------------------
RayFlashInterface::~RayFlashInterface(void)
{
}

//-------------------------------------------------------------------------------------
void RayFlashInterface::setupHikari()
{
	using namespace Hikari;
	
	hikariMgr = new HikariManager("..\\..\\media\\flash\\RayRayRayUI\\bin");
	
	controls = hikariMgr->createFlashOverlay("Menu", rayApp->hViewPort, 300, 300, Position(TopLeft));
	controls->load("RayRayRayUI.swf");
	controls->setDraggable(false);
	controls->setTransparent(true, true);
	//controls->bind("Rotate", FlashDelegate(this, &Interface::onRotateClick));
	
}