#include "stdafx.h"
#include "Player_Move.h"
#include"../Gamecamera.h"

Player_Move::Player_Move(Player* pla) :Player_State(pla)
{
}


Player_Move::~Player_Move()
{
}

void Player_Move::Update()
{
	CVector3 amount = CVector3::Zero();
	amount.x = g_pad->GetLStickXF();
	amount.z = g_pad->GetLStickYF();
	amount.y = 0.0f;
	if (amount.Length() > 0.0f)
	{
		CVector3 dir = amount;
		dir.Normalize();
		CVector3 camer_front = m_player->Getcamera()->GetCameraFront();
		camer_front.y = 0.0f;
		camer_front.Normalize();
		float m_angle = acos(dir.Dot(CVector3::AxisZ()));
		if (dir.x < 0)
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
		if (amount.Length() >= 0.3f)
		{
			m_player->ChangeAnimation(Player::run);
		}
		else
		{
			m_player->ChangeAnimation(Player::walk);
		}
	}
	else
	{
		m_player->ChangeAnimation(Player::idle);
	}
	m_player->Setspeed(amount.Length());
	if (g_pad[0].IsTrigger(enButtonX)) {
		m_player->TransitionState(Player::State_Attack);
	}
	else if (g_pad[0].IsTrigger(enButtonRB1))
	{
		m_player->TransitionState(Player::State_Guard);
	}
}