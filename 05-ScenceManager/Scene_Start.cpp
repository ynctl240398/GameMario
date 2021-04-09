#include "Scene_Start.h"





void Scene_Start::Render()
{
	animation_set->at(0)->Render(x, y, 255);
	
}

void Scene_Start::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + SCENE_START_BOX_WIDTH;
	b = y + SCENE_START_BOX_HEIGHT;
}



