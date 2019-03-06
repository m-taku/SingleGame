#pragma once
#include "Player_State.h"
class Player_Attack :public Player_State
{
public:
	Player_Attack(Player* player);
	~Player_Attack();
	void Update();
private:
	bool m_Hit = false;										//UŒ‚‚ğ“–‚Ä‚½‚©‚Ç‚¤‚©i“–‚Ä‚½‚ç”»’è‚ğÁ‚·j
};

