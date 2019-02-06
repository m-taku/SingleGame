#pragma once
#include"Player_State.h"
class Player_Die :public Player_State
{
public:
	Player_Die(Player* player);
	~Player_Die();
	void Update();
private:
	bool m_flag = true;
};

