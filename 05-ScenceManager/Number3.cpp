#include "Number3.h"





void Number3::Render()
{
	
	animation_set->at(0)->Render(x, y, 255);
	
}

void Number3::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + NUMBER_BOX_WIDTH;
	b = y + NUMBER_BOX_HEIGHT;
}


