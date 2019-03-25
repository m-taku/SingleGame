#include "stdafx.h"
#include "Player_Attack.h"
#include"../Gamecamera.h"
namespace {
	//剣のサイズ（aabb用）(縦、横、高さ)
	const CVector3 SWODSIZE = { 10.0f, 10.0f,80.0f };
}
Player_Attack::Player_Attack(Player* pla) :Player_State(pla)
{
	m_player->SetSpeed(0.0f);
	FindSwordpos();
	m_oldSwordcenter = m_Swordcenter;
	m_oldhandpos = m_handpos;
	m_player->ChangeAnimation(Player::attack);
	//ここからエフェクトの初期化
	{
		m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GeteffekseerManager(), (const EFK_CHAR*)L"Assets/efect/soad1.efk");
		m_playEffectHandle = g_graphicsEngine->GeteffekseerManager()->Play(m_sampleEffect, m_player->Get3Dposition().x, m_player->Get3Dposition().y, m_player->Get3Dposition().z);
		auto front = m_player->GetFront();
		float angle = acos(CVector3::AxisZ().Dot(front));
		auto k = CVector3::AxisZ();
		k.Cross(front);
		if (k.y >= 0.0f)
		{
			k = CVector3::AxisY();
		}
		else
		{
			k = CVector3::AxisY()*-1;
		}
		g_graphicsEngine->GeteffekseerManager()->SetRotation(m_playEffectHandle, { k.x,k.y,k.z }, angle);
	}
}
Player_Attack::~Player_Attack()
{
	m_sampleEffect->Release();
	g_graphicsEngine->GeteffekseerManager()->StopEffect(m_playEffectHandle);
}
void Player_Attack::Update()
{
	FindSwordpos();
	m_player->ChangeAnimation(Player::attack);
	if (m_player->IsEvent()) {
		//アニメーションイベントの発生中ならば
		auto attackMove = (m_Swordcenter - m_oldSwordcenter) / 2;
		auto hitpoint = attackMove + m_Swordcenter;
		//当たり判定発生
		GetHitObjict().HitTest(hitpoint, 100.0f, m_player->GetStatu().m_Attack, HitReceive::enemy);
		m_player->SetDebegvector(hitpoint);
	}
	m_oldSwordcenter = m_Swordcenter;
	if (!m_player->GetAnimationPlaying()) {
		//アニメーションが終了したので終了する
		m_player->TransitionState(Player::State_Move);
	}
}
void Player_Attack::FindSwordpos()
{
	//手のボーンから行列を取得
	CMatrix BoneMatrix = m_player->GetArmMatrix();
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