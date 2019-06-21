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
	//‚±‚±‚©‚çˆÚ“®ˆ—
	if (amount.Length() > 0.0f)
	{
		CVector3 dir = amount;
		dir.Normalize();
		CVector3 camer_front = m_player->GetCamera()->GetCameraFront();
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
		m_player->SetRotation(rod);
		if (amount.Length() >= 0.5f)
		{
			m_player->SetAnimType(Player::run);
		}
		else
		{
			m_player->SetAnimType(Player::walk);
		}
	}
	else
	{
		m_player->SetAnimType(Player::idle);
	}
	m_player->SetSpeed(amount.Length()*m_player->GetBairitu(speed1));
	if (g_pad[0].IsTrigger(enButtonX)) {
		m_player->SetAnimType(Player::combo1);
		m_player->TransitionState(Player::State_Attack);
	}
	else if (g_pad[0].IsTrigger(enButtonY))
	{
		m_player->SetAnimType(Player::Strength1);
		m_player->TransitionState(Player::State_Attack);
	}
	else if (g_pad[0].IsTrigger(enButtonB))
	{
		m_player->TransitionState(Player::State_Special);

	}
	else if (g_pad[0].IsTrigger(enButtonRB1))
	{
		m_player->TransitionState(Player::State_Guard);
	}

}