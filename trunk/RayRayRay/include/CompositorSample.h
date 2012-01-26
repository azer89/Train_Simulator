
#ifndef _CompositorChainReaction_H_
#define _CompositorChainReaction_H_

#include "Ogre.h"

using namespace Ogre;

// Class to handle post processing effect
class CompositorSample
{
public:
	CompositorSample();

	void setupCompositorContent(void);
	void cleanupContent(void);
	void setCompositorEnabled(Ogre::String name, bool enabled);

	void SetMotionBlur(bool enabled);

public:
	Ogre::Camera* mCamera;
	Ogre::Viewport* mViewport;

protected:
	void setupView(void);
	void setupControls(void);
	void setupScene(void);
	void createEffects(void);
	void createTextures(void);
	void registerCompositors();

protected:
	TextureUnitState* mDebugTextureTUS;
	bool isMotionBlurActive;
};


#endif