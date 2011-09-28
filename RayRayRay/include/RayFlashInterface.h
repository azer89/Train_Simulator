
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

	Hikari::HikariManager* hikariMgr;
	Hikari::FlashControl* controls;
	void setupHikari();

private:
	RayRayRay* rayApp;
};