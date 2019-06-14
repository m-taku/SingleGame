#include "stdafx.h"
#include "Player_Hit.h"


Player_Hit::Player_Hit(Player* pla) :Player_State(pla)
{
	m_player->SetSpeed(0.0f);
	//m_player->SetAnimType(Player::idle);
	m_player->SetAnimType(Player::hit);
}
Player_Hit::~Player_Hit()
{
}
void Player_Hit::Update()
{

	if (!m_player->GetAnimationPlaying()) {
		//アニメーションが終了したのでもとに戻る
		m_player->TransitionState(Player::State_Move);
	}
}