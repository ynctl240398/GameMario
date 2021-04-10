#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.1f 

#define MARIO_JUMP_SPEED_Y			0.45f
#define MARIO_JUMP_DEFLECT_SPEED	0.5f
#define MARIO_FIGHT_SPEED_X			1.0f
#define MARIO_SIT_SPEED_Y			0.5f


#define MARIO_GRAVITY				0.002f
#define MARIO_DIE_DEFLECT_SPEED		0.5f


#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_SIT             400
#define MARIO_STATE_DIE				500
#define MARIO_STATE_FIGHT			600

#define MARIO_ANI_SMALL_IDLE_RIGHT			0
#define MARIO_ANI_SMALL_IDLE_LEFT			1
#define MARIO_ANI_SMALL_WALKING_RIGHT		2
#define MARIO_ANI_SMALL_WALKING_LEFT		3
#define MARIO_ANI_SMALL_JUMP_RIGHT			4
#define MARIO_ANI_SMALL_JUMP_LEFT			5
#define MARIO_ANI_DIE						6

#define MARIO_ANI_BIG_IDLE_RIGHT			7
#define MARIO_ANI_BIG_IDLE_LEFT				8
#define MARIO_ANI_BIG_WALKING_RIGHT			9
#define MARIO_ANI_BIG_WALKING_LEFT			10
#define MARIO_ANI_BIG_JUMP_RIGHT			11
#define MARIO_ANI_BIG_JUMP_LEFT				12
#define MARIO_ANI_BIG_SIT_RIGHT				13
#define MARIO_ANI_BIG_SIT_LEFT				14

#define MARIO_ANI_FIGHT_IDLE_RIGHT			15
#define MARIO_ANI_FIGHT_IDLE_LEFT			16
#define MARIO_ANI_FIGHT_WALKING_RIGHT		17
#define MARIO_ANI_FIGHT_WALKING_LEFT		18
#define MARIO_ANI_FIGHT_JUMP_RIGHT			19
#define MARIO_ANI_FIGHT_JUMP_LEFT			20
#define MARIO_ANI_FIGHT_SIT_RIGHT			21
#define MARIO_ANI_FIGHT_SIT_LEFT			22
#define MARIO_ANI_FIGHT_RIGHT				23
#define MARIO_ANI_FIGHT_LEFT				24


#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIGHT	3

#define MARIO_SMALL_BBOX_WIDTH  15
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_BIG_BBOX_SIT_WIDTH	14
#define MARIO_BIG_BBOX_SIT_HEIGHT	18

#define MARIO_BIG_BBOX_WIDTH  16
#define MARIO_BIG_BBOX_HEIGHT 27



#define MARIO_UNTOUCHABLE_TIME 5000




class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	float start_x;			// initial position of Mario at scene
	float start_y;
public:
	boolean isJump;
	boolean isFight;
	
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { level = l; }
	int GetLevel() { return this->level; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};