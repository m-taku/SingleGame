#include "stdafx.h"
#include "EnemyStateDefens.h"



EnemyStateDefens::EnemyStateDefens(Enemy* enamy, const CVector3* pos) :EnemyState(enamy, pos)
{
	m_enemy->AI(m_raitspeed, m_kakudo);
}



EnemyStateDefens::~EnemyStateDefens()
{

	m_enemy->SetRightSpeed(0.0f);
}
void EnemyStateDefens::Update() 
{
	auto distance = GetTarget2DPosition() - m_enemy->Get2DPosition();
	switch (m_steat)
	{
	case Wait:
		if (distance.Length() <= 200.0f) {
			m_enemy->AddAngle(distance);
			m_enemy->SetRightSpeed(m_raitspeed);
			m_enemy->SetFrontSpeed(0.0f);
			m_enemy->ChangeAnimation(Enemy::idle);
		}
		else
		{
			m_steat = Chase;
		}
		break;
	case Chase:
		m_enemy->AddAngle(distance);
		m_enemy->ChangeAnimation(Enemy::walk);
		m_enemy->SetRightSpeed(0.0f);
		m_enemy->SetFrontSpeed(1.0f / 2.0f);
		if (distance.Length() <= 200.0f)
		{
			m_steat = Wait;
		}
		break;
	default:
		break;
	}
	if (distance.Length() >= 300.0f)
	{
		m_enemy->SetFrontSpeed(1.0f);
		m_enemy->TransitionState(Enemy::State_Move);
	}
	else {
		m_enemy->AIDefens(m_kakudo);
	}
}
