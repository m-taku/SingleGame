#pragma once
#include"Player_State.h"
class Player_Hit :public Player_State
{
public:
	Player_Hit(Player* player);
	~Player_Hit();
	void Update();

};

