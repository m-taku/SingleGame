#include "stdafx.h"
#include "Player_Special.h"

//�Ó]���o
Player_Special::Player_Special(Player* pla) :Player_State(pla)
{
	m_player->SetSpeed(0.0f);
	if (m_player->GetStatu().m_MP < m_player->p_status->m_MP) {
		ka = chrji;

		m_player->SetAnimType(Player::defens);
	}
	else
	{
		m_sampleEffect = Effekseer::Effect::Create(g_graphicsEngine->GetEffekseerManager(), (const EFK_CHAR*)L"Assets/efect/Spetyrl.efk");
		m_playEffectHandle = g_graphicsEngine->GetEffekseerManager()->Play(m_sampleEffect, m_player->Get3DPosition().x, m_player->Get3DPosition().y, m_player->Get3DPosition().z);
		m_player->ReverseHit();
		m_player->SetAnimType(Player::SPattack);
		m_bgmA.Init(L"Assets/sound/fire4.wav");
		ka = Attackc;
	}
}


Player_Special::~Player_Special()
{

}
void Player_Special::Update()
{
	switch (ka)
	{
	case Player_Special::chrji:
		if (g_pad[0].IsPress(enButtonB)) {
			m_player->AddMp(1.0f);
			if (m_player->GetStatu().m_MP >= m_player->p_status->m_MP) {
				m_player->TransitionState(Player::State_Move);
			}
		}
		else {
			m_player->TransitionState(Player::State_Move);
		}
		break;
	case Player_Special::Attackc:
		Attack();
		break;
	default:
		break;
	}

}
void Player_Special::Attack()
{
	
	if (m_player->IsEvent(0)) {
		//�����蔻�蔭��
		auto attack = m_player->GetStatu().m_Attack*m_player->GetBairitu(attakc1)*2.0f;
		//						���X�e�[�^�X					���A�C�e���Ȃǂɂ��{��	
		GetHitObjict().HitTest(m_player->Get2DPosition(), m_scuea, attack, HitReceive::enemy);
	}
	m_scuea += 5.0f;
	if (m_player->IsEvent(1)&&m_sound==false) {
		m_bgmA.Play(false); 
		m_sound = true;
	}
	if (!m_player->GetAnimationPlaying())
	{

		m_player->ReverseHit();
		//�A�j���[�V�������I�������̂ŏI������
		m_sampleEffect->Release();
		if (g_graphicsEngine->GetEffekseerManager() != NULL) {
			g_graphicsEngine->GetEffekseerManager()->StopEffect(m_playEffectHandle);
		}
		m_player->AddMp(-m_player->p_status->m_MP);
		m_player->TransitionState(Player::State_Move);
	}
}