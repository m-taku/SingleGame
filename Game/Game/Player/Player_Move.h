#pragma once
#include "Player_State.h"
class Player_Move :public Player_State
{
public:
	Player_Move(Player* player);
	~Player_Move();
	void Update();
private:
	CVector3 m_speed = CVector3::Zero();
};

