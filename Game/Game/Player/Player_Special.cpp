#include "stdafx.h"
#include "Player_Special.h"


Player_Special::Player_Special(Player* pla) :Player_State(pla)
{

	m_player->SetSpeed(0.0f);
	//m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/efect/Spetyrl.efk");
	//m_playEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(m_sampleEffect, m_player->Get3DPosition().x, m_player->Get3DPosition().y, m_player->Get3DPosition().z);
	m_player->ReverseHit();
}


Player_Special::~Player_Special()
{
	//m_sampleEffect->Release();
	//if (g_graphicsEngine->GetEffekseerManager() != NULL) {
	//	g_graphicsEngine->GetEffekseerManager()->StopEffect(m_playEffectHandle);
	//}
}
void Player_Special::Update()
{
	if (m_player->IsEvent(0)) {
		//当たり判定発生
		auto attack = m_player->GetStatu().m_Attack*m_player->GetBairitu(attakc1)*3.0f;
		//						↑ステータス					↑アイテムなどによる倍率	
		GetHitObjict().HitTest(m_player->Get2DPosition(), m_scuea, attack, HitReceive::enemy);
	}
	m_scuea += 10.0f;
	if (!m_player->GetAnimationPlaying()) 
	{

		m_player->ReverseHit();
		//アニメーションが終了したので終了する
		m_player->TransitionState(Player::State_Move);
	}
}
