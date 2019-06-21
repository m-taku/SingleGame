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
	case Player::Strength1:
		//m_player->SetSpeed(0.1f);
		combobai = 1.2;
		break;
	case Player::Strength2:
		//m_player->SetSpeed(0.1f);
		combobai = 1.5;
		break;
	case Player::combo1:
	case Player::combo2:
		break;
	case Player::combo3:
		combobai = 1.2f;
		break;
	default:
		break;
	}
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
		m_player->SetDebegVector(hitpoint, {0.0f,1.0f,0.0f}, 30.0f);
		GetHitObjict().HitTest(hitpoint, 80.0f, attack, HitReceive::enemy);

	}	
	m_oldSwordcenter = m_Swordcenter;
	//コンボの判定
	if ((m_storong != true || m_combo != true) && m_player->IsEvent(combo)) {
		auto pos = m_player->Get2DPosition();
		pos.y += 50.0f;
		//m_player->SetDebeg(pos);
		if(g_pad[0].IsTrigger(enButtonX)) {
			m_combo = true;
		}
		if (g_pad[0].IsTrigger(enButtonY))
		{
			m_storong = true;
		}
	}
	if (!m_player->GetAnimationPlaying()) {
		if (m_combo)
		{
			int k=attackNo+1;
			m_player->SetAnimType((Player::animation)k);
			m_player->TransitionState(Player::State_Attack);
		}
		else if (m_storong)
		{
			int k = attackNo -2;
			m_player->SetAnimType((Player::animation)k);
			m_player->TransitionState(Player::State_Attack);

		}else
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
	m_Swordcenter.x = m_handpos.x + m_Up.x*SWODSIZE.z/2.0f;
	m_Swordcenter.y = m_handpos.y + m_Up.y*SWODSIZE.z/2.0f;
	m_Swordcenter.z = m_handpos.z + m_Up.z*SWODSIZE.z/2.0f;
}