#pragma once
#include "GameObject.h"
#define NUMBER_BOX_WIDTH 42
#define NUMBER_BOX_HEIGHT 41

class Number3 : public CGameObject
{
public:
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

};

