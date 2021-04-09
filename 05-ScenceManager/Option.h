#pragma once
#include"GameObject.h"
#define OPTION_BOX_WIDTH  112
#define OPTION_BOX_HEIGHT 24

#define OPTION_STATUS_0	100
#define OPTION_STATUS_1	200
#define OPTION_STATUS_2	300

#define OPTION_ANI_0 0
#define OPTION_ANI_1 1
#define OPTION_ANI_2 2
class Option : public CGameObject
{
public:
	Option();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	
	
};

