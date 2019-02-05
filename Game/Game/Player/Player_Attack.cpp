#include "stdafx.h"
#include "Player_Attack.h"
#include"Player/Player.h"


Player_Attack::Player_Attack(Player* pla) :Player_State(pla)
{
	m_player->Setspeed(0.0f);
	CVector3 atari = m_player->Get3Dposition();
	atari.y += 100.0f;
	atari += m_player->GetFront() * 100.0f;
	g_HitObjict->HitTest(atari, HitReceive::enemy);
}


Player_Attack::~Player_Attack()
{
}
void Player_Attack::Update()
{
	m_player->ChangeAnimation(Player::attack);
	CVector3 atari = m_player->Get3Dposition();
	atari.y += 100.0f;
	atari += m_player->GetFront() * 100.0f;
	g_HitObjict->HitTest(atari, HitReceive::enemy);
	if (!m_player->GetanimationPlaying()) {
		m_player->TransitionState(Player::State_Move);
	}
	//if (m_player->g)
	//{
	//	m_player->ChangeAnimation(Player::walk);
	//	m_attac = false;
	//}
	//else {
		//auto ka = m_position;
		//ka.y += 100.0f;
		//ka += m_Front * 100.0f;
		//m_debugVector->Update(ka);
		//m_hit->HitTest(ka, HitReceive::player);
	//}
}
