#pragma once
#include "Player_State.h"
class Player_Guard :public Player_State
{
public:
	Player_Guard(Player* player);
	~Player_Guard();
	void Update();
};

