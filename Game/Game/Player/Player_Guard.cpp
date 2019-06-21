#include "stdafx.h"
#include "Player_Guard.h"
#include"../Gamecamera.h"


Player_Guard::Player_Guard(Player* pla) :Player_State(pla)
{
	m_player->SetSpeed(0.0f); 
	
	m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/efect/baria.efk");
	m_playEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(m_sampleEffect, m_player->Get3DPosition().x, m_player->Get3DPosition().y, m_player->Get3DPosition().z);
	g_graphicsEngine->GetEffekseerManager()->SetScale(m_playEffectHandle,4.0f,4.0f,4.0f);
	//m_player->ReverseHit();
}



Player_Guard::~Player_Guard()
{
	//アニメーションが終了したので終了する
	m_sampleEffect->Release();
	if (g_graphicsEngine->GetEffekseerManager() != NULL) {
		g_graphicsEngine->GetEffekseerManager()->StopEffect(m_playEffectHandle);
	}
}
void Player_Guard::Update()
{

	if (g_pad[0].IsPress(enButtonRB1))
	{

		m_player->SetAnimType(Player::defens);

	}
	else

	{
		//m_player->ReverseHit();
		m_player->TransitionState(Player::State_Move);
	}
}

