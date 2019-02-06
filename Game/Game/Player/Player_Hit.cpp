#include "stdafx.h"
#include "Player_Hit.h"


Player_Hit::Player_Hit(Player* pla) :Player_State(pla)
{
	m_player->Setspeed(0.0f);
	m_player->ChangeAnimation(Player::hit);
}
Player_Hit::~Player_Hit()
{
}
void Player_Hit::Update()
{
	if (!m_player->GetanimationPlaying()) {
		m_player->TransitionState(Player::State_Move);
	}
}