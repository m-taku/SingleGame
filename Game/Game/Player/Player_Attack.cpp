#include "stdafx.h"
#include "Player_Attack.h"
#include"../Gamecamera.h"
namespace {
	//剣のサイズ（aabb用）(縦、横、高さ)
	const CVector3 SWODSIZE = { 10.0f, 10.0f,80.0f };
}
Player_Attack::Player_Attack(Player* pla) :Player_State(pla)
{
	m_player->Setspeed(0.0f);
	FindSwordpos();
	m_oldSwordcenter = m_Swordcenter;
	m_oldhandpos = m_handpos;
	m_player->ChangeAnimation(Player::attack);
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
	if (!m_Hit) {
		if (m_player->IsEvent()) {
			CVector3 atari = m_player->Get3Dposition();
			atari.y += 50.0f;
			atari += m_player->GetFront() * 50.0f;
			m_Hit = GetHitObjict().HitTest(atari, m_player->GetStatu().m_Attack, HitReceive::enemy);
		}
	}
	if (!m_player->GetanimationPlaying()) {
		m_player->TransitionState(Player::State_Move);
	}
}
void Player_Attack::FindSwordpos()
{
	CMatrix BoneMatrix;
	m_handpos.x = BoneMatrix.m[3][0];
	m_handpos.y = BoneMatrix.m[3][1];
	m_handpos.z = BoneMatrix.m[3][2];
	m_Up.x = BoneMatrix.m[2][0];
	m_Up.y = BoneMatrix.m[2][1];
	m_Up.z = BoneMatrix.m[2][2];
	m_Up.Normalize();
	m_Swordcenter.x = m_handpos.x + m_Up.x*SWODSIZE.z / 2;
	m_Swordcenter.y = m_handpos.y + m_Up.y*SWODSIZE.z / 2;
	m_Swordcenter.z = m_handpos.z + m_Up.z*SWODSIZE.z / 2;
}