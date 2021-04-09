#pragma once
#include "GameObject.h"

#define SCENE_START_BOX_WIDTH 320
#define SCENE_START_BOX_HEIGHT 240
class Scene_Start : public CGameObject
{
	
public:

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

};

