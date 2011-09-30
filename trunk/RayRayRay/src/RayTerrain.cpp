#include "Stdafx.h"
#include "RayTerrain.h"

//-------------------------------------------------------------------------------------
RayTerrain::RayTerrain(void)
{
}
//-------------------------------------------------------------------------------------
RayTerrain::~RayTerrain(void)
{
	OGRE_DELETE mTerrainGroup;
    OGRE_DELETE mTerrainGlobals;
}

//-------------------------------------------------------------------------------------
void RayTerrain::createTerrain(Ogre::SceneManager* mSceneMgr, Ogre::Light* light)
{
	this->mSceneMgr = mSceneMgr;

	mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();

	// still not work
	//mTerrainGlobals->setCastsDynamicShadows(true);
	//mTerrainGlobals->setLightMapDirection(light->getDirection());

	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(this->mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 65, 1000.f);
	
    mTerrainGroup->setFilenameConvention(Ogre::String("RayRayRay"), Ogre::String("dat"));
    mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
	
    configureTerrainDefaults(light);
 
    for (long x = 0; x <= 0; ++x)
        for (long y = 0; y <= 0; ++y)
            defineTerrain(x, y);
 
    // sync load since we want everything in place when we start
    mTerrainGroup->loadAllTerrains(true);
	
    if (mTerrainsImported)
    {
        Ogre::TerrainGroup::TerrainIterator ti = mTerrainGroup->getTerrainIterator();
        while(ti.hasMoreElements())
        {
            Ogre::Terrain* t = ti.getNext()->instance;
			
			t->getMaterial()->setReceiveShadows(true);

            initBlendMaps(t);
        }
    }
 
    mTerrainGroup->freeTemporaryResources();
}

//-------------------------------------------------------------------------------------
bool RayTerrain::getTerrainsImported(void)
{
	return this->mTerrainsImported;
}

//-------------------------------------------------------------------------------------
void RayTerrain::setTerrainsImported(bool val)
{
	this->mTerrainsImported = val;
}

//-------------------------------------------------------------------------------------
Ogre::TerrainGlobalOptions* RayTerrain::getTerrainGlobals(void)
{
	return this->mTerrainGlobals;
}

//-------------------------------------------------------------------------------------
Ogre::TerrainGroup* RayTerrain::getTerrainGroup(void)
{
	return this->mTerrainGroup;
}


//-------------------------------------------------------------------------------------
void RayTerrain::getTerrainImage(bool flipX, bool flipY, Ogre::Image& img)
{
	img.load("terrain.png", 
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    if (flipX) img.flipAroundY();
    if (flipY) img.flipAroundX();
	
}
//-------------------------------------------------------------------------------------
void RayTerrain::defineTerrain(long x, long y)
{
	Ogre::String filename = mTerrainGroup->generateFilename(x, y);
    if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), filename))
    {
        mTerrainGroup->defineTerrain(x, y);
    }
    else
    {
        Ogre::Image img;
        getTerrainImage(x % 2 != 0, y % 2 != 0, img);
        mTerrainGroup->defineTerrain(x, y, &img);
        mTerrainsImported = true;
    }
}
//-------------------------------------------------------------------------------------
void RayTerrain::initBlendMaps(Ogre::Terrain* terrain)
{
	
	Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
    Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);
    Ogre::Real minHeight0 = 40;
    Ogre::Real fadeDist0 = 20;
    Ogre::Real minHeight1 = 20;
    Ogre::Real fadeDist1 = 5;
    float* pBlend1 = blendMap1->getBlendPointer();
    for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
    {
        for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
        {
            Ogre::Real tx, ty;
 
            blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
            Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
            Ogre::Real val = (height - minHeight0) / fadeDist0;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
 
            val = (height - minHeight1) / fadeDist1;
            val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
            *pBlend1++ = val;
        }
    }
    blendMap0->dirty();
    blendMap1->dirty();
    blendMap0->update();
    blendMap1->update();
}

//-------------------------------------------------------------------------------------
void RayTerrain::configureTerrainDefaults(Ogre::Light* light)
{
	// Configure global
    mTerrainGlobals->setMaxPixelError(8);
    // testing composite map
    mTerrainGlobals->setCompositeMapDistance(3000);
	//mTerrainGlobals->setCastsDynamicShadows(true);
	
    // Important to set these so that the terrain knows what to use for derived (non-realtime) data
    mTerrainGlobals->setLightMapDirection(light->getDerivedDirection());
    mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
    mTerrainGlobals->setCompositeMapDiffuse(light->getDiffuseColour());
	
    // Configure default import settings for if we use imported image
    Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
    defaultimp.terrainSize = 65;
    defaultimp.worldSize = 1000.0f;
	defaultimp.inputScale = 50;
    defaultimp.minBatchSize = 33;
    defaultimp.maxBatchSize = 65;
	
	// textures	
    defaultimp.layerList.resize(3);
	defaultimp.layerList[0].worldSize = 10;
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
    defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
    defaultimp.layerList[1].worldSize = 30;
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
    defaultimp.layerList[2].worldSize = 20;
    defaultimp.layerList[2].textureNames.push_back("grass_green-01_diffusespecular.dds");
    defaultimp.layerList[2].textureNames.push_back("grass_green-01_normalheight.dds");
}