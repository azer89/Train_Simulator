
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
	
	Ogre::TerrainGlobalOptions* mTerrainGlobals;	// terrain options
    Ogre::TerrainGroup* mTerrainGroup;				// terrain group
	Ogre::SceneManager* mSceneMgr;					// scene manager
    bool mTerrainsImported;							// is already imported
 
    void defineTerrain(long x, long y);
    void initBlendMaps(Ogre::Terrain* terrain);
    void configureTerrainDefaults(Ogre::Light* light);
	void getTerrainImage(bool flipX, bool flipY, Ogre::Image& img);

};