#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "GameObject.h"
#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"



CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_FIGHT;
	SetState(MARIO_STATE_IDLE);
	untouchable = 0;
	isJump = false;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += MARIO_GRAVITY * dt;


	if (dy == 0)
	{
		isJump = false;

	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba *>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			} // if Goomba
			else if (dynamic_cast<CPortal *>(e->obj))
			{
				CPortal *p = dynamic_cast<CPortal *>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
		}
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{

	int ani;
	if (state == MARIO_STATE_DIE)
	{
		ani = MARIO_ANI_DIE;
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		if (state == MARIO_STATE_IDLE)
		{
			if (this->isJump == true && ny <= 0) {
				if (nx > 0) ani = MARIO_ANI_SMALL_JUMP_RIGHT;
				else ani = MARIO_ANI_SMALL_JUMP_LEFT;
			}
			else {
				if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
				else ani = MARIO_ANI_SMALL_IDLE_LEFT;
			}
		}
		else if (this->isJump == true && ny <= 0) {
			if (nx > 0) ani = MARIO_ANI_SMALL_JUMP_RIGHT;
			else ani = MARIO_ANI_SMALL_JUMP_LEFT;
		}
		else if (state == MARIO_STATE_WALKING_RIGHT)
			ani = MARIO_ANI_SMALL_WALKING_RIGHT;
		else if (state == MARIO_STATE_WALKING_LEFT)
			ani = MARIO_ANI_SMALL_WALKING_LEFT;

	}
	else if (level == MARIO_LEVEL_BIG)
	{
		if (state == MARIO_STATE_IDLE)
		{
			if (this->isJump == true && ny <= 0) {
				if (nx > 0) ani = MARIO_ANI_BIG_JUMP_RIGHT;
				else ani = MARIO_ANI_BIG_JUMP_LEFT;
			}
			else {
				if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
				else ani = MARIO_ANI_BIG_IDLE_LEFT;
			}
		}
		else if (this->isJump == true && ny <= 0)
		{
			if (nx > 0) ani = MARIO_ANI_BIG_JUMP_RIGHT;
			else ani = MARIO_ANI_BIG_JUMP_LEFT;
		}
		else if (state == MARIO_STATE_SIT)
		{
			if (nx > 0) ani = MARIO_ANI_BIG_SIT_RIGHT;
			else ani = MARIO_ANI_BIG_SIT_LEFT;
		}
		else if (state == MARIO_STATE_WALKING_RIGHT)
			ani = MARIO_ANI_BIG_WALKING_RIGHT;
		else if (state == MARIO_STATE_WALKING_LEFT)
			ani = MARIO_ANI_BIG_WALKING_LEFT;
	}else if (level == MARIO_LEVEL_FIGHT)
	{

		if (state == MARIO_STATE_IDLE)
		{
			if (this->isJump == true && ny <= 0) {
				if (nx > 0) ani = MARIO_ANI_FIGHT_JUMP_RIGHT;
				else ani = MARIO_ANI_FIGHT_JUMP_LEFT;
			}
			else {
				if (nx > 0) ani = MARIO_ANI_FIGHT_IDLE_RIGHT;
				else ani = MARIO_ANI_FIGHT_IDLE_LEFT;
			}
		}
		else if (state == MARIO_STATE_FIGHT) {
			if (nx >= 0) ani = MARIO_ANI_FIGHT_RIGHT;
			else ani = MARIO_ANI_FIGHT_LEFT;
		}
		else if (state == MARIO_STATE_SIT) {
			if (nx > 0) ani = MARIO_ANI_FIGHT_SIT_RIGHT;
			else ani = MARIO_ANI_FIGHT_SIT_LEFT;
		} 
		else if (this->isJump == true && ny <= 0)
		{
			if (nx > 0) ani = MARIO_ANI_FIGHT_JUMP_RIGHT;
			else ani = MARIO_ANI_FIGHT_JUMP_LEFT;
		}
		else if (state == MARIO_STATE_WALKING_RIGHT) {
			 ani = MARIO_ANI_FIGHT_WALKING_RIGHT;
		}
		else if (state == MARIO_STATE_WALKING_LEFT) {
			 ani = MARIO_ANI_FIGHT_WALKING_LEFT;
		}
	}

	animation_set->at(ani)->Render(x, y, 255);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		this->isJump = true;
		vy = -MARIO_JUMP_SPEED_Y;
		ny = -1;
		break;
	case MARIO_STATE_SIT:
		vy = MARIO_SIT_SPEED_Y;
		ny = 1;
		vx = 0;
		
		break;
	case MARIO_STATE_IDLE:
		vx = 0;
		ny = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_FIGHT:
		vx = 0;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state != MARIO_STATE_DIE && (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_FIGHT))
	{
		if (y + MARIO_BIG_BBOX_WIDTH > 150)
		{
			y = 150 - MARIO_BIG_BBOX_HEIGHT - 1;
		}
	}
	top = y;
	left = x;

	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_FIGHT)
	{
		if (state == MARIO_STATE_SIT)
		{
			right = x + MARIO_BIG_BBOX_SIT_WIDTH;
			bottom = y + MARIO_BIG_BBOX_SIT_HEIGHT;
		}
		else {
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else {
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}

}

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}

