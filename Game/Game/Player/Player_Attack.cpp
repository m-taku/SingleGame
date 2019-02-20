#include "stdafx.h"
#include "Player_Attack.h"
#include"../Gamecamera.h"


Player_Attack::Player_Attack(Player* pla) :Player_State(pla)
{
	m_player->Setspeed(0.0f);
	CVector3 atari = m_player->Get3Dposition();
	atari.y += 100.0f;
	atari += m_player->GetFront() * 100.0f;
	//g_HitObjict->HitTest(atari, m_player->GetStatu().Attack, HitReceive::enemy);
}


Player_Attack::~Player_Attack()
{
}
void Player_Attack::Update()
{
	CVector3 m_amount = CVector3::Zero();
	m_amount.x = g_pad->GetLStickXF();
	m_amount.z = g_pad->GetLStickYF();
	m_amount.y = 0.0f;
	if (m_amount.Length() > 0.0f)
	{
		CVector3 amount = m_amount;
		amount.Normalize();
		CVector3 camer_front = m_player->Getcamera()->GetCameraFront();
		camer_front.y = 0.0f;
		camer_front.Normalize();
		float m_angle = acos(amount.Dot(CVector3::AxisZ()));
		if (amount.x < 0)
		{
			m_angle *= -1;
		}
		float camer_angle = acos(camer_front.Dot(CVector3::AxisZ()));
		CVector3 camer_jiku;
		camer_jiku.Cross(camer_front, CVector3::AxisZ());
		if (camer_jiku.y > 0)
		{
			camer_angle *= -1;
		}
		m_angle += camer_angle;
		CQuaternion rod;
		rod.SetRotation(CVector3::AxisY(), m_angle);
		m_player->Setrotation(rod);
		m_player->Setspeed(0.5f);
		//m_player->ChangeAnimation(Player::walk);
	}
	else
	{
		m_player->Setspeed(0.0f);
	}
	m_player->ChangeAnimation(Player::attack);
	if (true) {
		CVector3 atari = m_player->Get3Dposition();
		atari.y += 50.0f;
		atari += m_player->GetFront() * 50.0f;
		g_HitObjict->HitTest(atari, m_player->GetStatu().Attack, HitReceive::enemy);
	}
	if (!m_player->GetanimationPlaying()) {
		m_player->TransitionState(Player::State_Move);
	}
}
