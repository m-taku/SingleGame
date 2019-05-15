#include "stdafx.h"
#include "Player_Die.h"
#include"../Gameover.h"

Player_Die::Player_Die(Player* pla) :Player_State(pla)
{
	m_player->ChangeAnimation(Player::ded);
	m_player->SetAnimType(Player::ded);
	m_player->SetSpeed(0.0f);
}

Player_Die::~Player_Die()
{
}
void Player_Die::Update()
{
	
	if (!m_player->GetAnimationPlaying()&& m_die ==true) {
		//死亡したのでゲームオーバーになる
		if (nullptr == g_objectManager->FindGO<Gameover>("Gameover")) {
			g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover, "Gameover")->Setfra(false);
		}
		m_die = false;
	}
}