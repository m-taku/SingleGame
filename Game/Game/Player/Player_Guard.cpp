#include "stdafx.h"
#include "Player_Guard.h"
#include"../Gamecamera.h"


Player_Guard::Player_Guard(Player* pla) :Player_State(pla)
{
	m_player->SetSpeed(0.0f);
	m_player->ReverseHit();
}


Player_Guard::~Player_Guard()
{
}
void Player_Guard::Update()
{

	if (g_pad[0].IsPress(enButtonRB1))
	{
		m_player->ChangeAnimation(Player::defens);
	}
	else
	{
		m_player->TransitionState(Player::State_Move);
		m_player->ReverseHit();
	}
}

