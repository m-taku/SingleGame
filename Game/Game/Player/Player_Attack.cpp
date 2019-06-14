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
	FindSwordPos();
	m_oldSwordcenter = m_Swordcenter;
	m_oldhandpos = m_handpos; 
	attackNo = m_player->GetAnimType();
	switch (attackNo)
	{
	case Player::combo1:
	case Player::combo2:
		break;
	case Player::combo3:
		combobai = 1.2f;
		break;
	default:
		break;
	}

	////ここからエフェクトの初期化
	// オミット
	//{

	//	auto front = m_player->GetFront();
	//	float angle = acos(CVector3::AxisZ().Dot(front));
	//	auto jiku = CVector3::AxisZ();
	//	jiku.Cross(front);
	//	if (jiku.y >= 0.0f)
	//	{
	//		jiku = CVector3::AxisY();
	//	}
	//	else
	//	{
	//		jiku = CVector3::AxisY()*-1;
	//	}
	//	CQuaternion k = CQuaternion::Identity(), ma;
	//	switch (m_player->GetAnimType())
	//	{
	//	case Player::combo1:
	//		g_graphicsEngine->GetEffekseerManager()->SetRotation(m_playEffectHandle, { 0.0f,0.0f,1.0f}, CMath::DegToRad(180.0f));
	//		ma.SetRotation(CVector3::AxisZ(), CMath::DegToRad(180.0f));
	//		break;
	//	case Player::combo2:
	//		break;
	//	case Player::combo3:
	//		g_graphicsEngine->GetEffekseerManager()->SetRotation(m_playEffectHandle, { 0.0f,0.0f,1.0f }, CMath::DegToRad(90.0f));

	//		ma.SetRotation(CVector3::AxisZ(), CMath::DegToRad(90.0f));
	//		break;
	//	default:
	//		break;
	//	}
	//	k.SetRotation(jiku, angle);
	//	//k.Multiply(ma);
	//	g_graphicsEngine->GetEffekseerManager()->SetRotation(m_playEffectHandle,k.x,k.y,k.z);
	//}
}
Player_Attack::~Player_Attack()
{

}
void Player_Attack::Update()
{
	FindSwordPos();
	if (m_player->IsEvent(attack)) {
		//アニメーションイベントの発生中ならば
		auto attackMove = (m_Swordcenter - m_oldSwordcenter) / 2;
		auto hitpoint = attackMove + m_Swordcenter;
		//当たり判定発生
		auto attack = m_player->GetStatu().m_Attack*m_player->GetBairitu(attakc1)*combobai;
		//						↑ステータス					↑アイテムなどによる倍率	

		GetHitObjict().HitTest(hitpoint, 100.0f, attack, HitReceive::enemy);

	}
	m_oldSwordcenter = m_Swordcenter;
	//コンボの判定
	if (m_combo != true && m_player->IsEvent(combo)) {
		auto pos = m_player->Get2DPosition();
		pos.y += 50.0f;
		m_player->SetDebegVector(pos);
		if(g_pad[0].IsTrigger(enButtonX)) {
			m_combo = true;
		}
	}
	if (!m_player->GetAnimationPlaying()) {
		if (m_combo)
		{
			int k=attackNo+1;
			m_player->SetAnimType((Player::animation)k);
			m_player->TransitionState(Player::State_Attack);
		}
		else
		{
			//アニメーションが終了したので終了する
			m_player->TransitionState(Player::State_Move);
		}
	}
}
void Player_Attack::FindSwordPos()
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