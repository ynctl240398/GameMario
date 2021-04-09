#include "Option.h"



Option::Option()
{
	state = OPTION_STATUS_0;;
}

void Option::Render()
{
	int ani = -1;
	switch (state) {
		case OPTION_STATUS_0: 
			ani = OPTION_ANI_0;
			break;
		case OPTION_STATUS_1:
			ani = OPTION_ANI_1;
			break;
		case OPTION_STATUS_2:
			ani = OPTION_ANI_2;
			break;
	}
	animation_set->at(ani)->Render(x, y, 255);
	
}

void Option::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + OPTION_BOX_WIDTH;
	b = y + OPTION_BOX_HEIGHT;
}



