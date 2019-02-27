#include "stdafx.h"
#include "Player_Die.h"
#include"../Gameover.h"

Player_Die::Player_Die(Player* pla) :Player_State(pla)
{
	m_player->ChangeAnimation(Player::ded);
	m_player->Setspeed(0.0f);
}

Player_Die::~Player_Die()
{
}
void Player_Die::Update()
{
	if (!m_player->GetanimationPlaying()&& m_flag==true) {
		g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover);
		m_flag = false;
	}
}