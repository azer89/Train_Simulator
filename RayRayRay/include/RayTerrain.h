
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

class RayTerrain
{
public:
    RayTerrain(void);
    virtual ~RayTerrain(void);

	void createTerrain(Ogre::SceneManager* mSceneMgr, Ogre::Light* light);
	bool getTerrainsImported(void);
	void setTerrainsImported(bool val);
	Ogre::TerrainGlobalOptions* getTerrainGlobals(void);
	Ogre::TerrainGroup* getTerrainGroup(void);

private:
	
	Ogre::TerrainGlobalOptions* mTerrainGlobals;
    Ogre::TerrainGroup* mTerrainGroup;
	Ogre::SceneManager* mSceneMgr;
    bool mTerrainsImported;
	Ogre::Image image;
 
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);
	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);

};