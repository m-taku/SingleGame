#include "stdafx.h"
#include "EnemyStateHit.h"
#include"Enemy.h"

EnemyStateHit::EnemyStateHit(Enemy* enamy, const CVector3* pos) :EnemyState(enamy,pos)
{

	m_enemy->ChangeAnimation(Enemy::attack);
	m_enemy->ChangeAnimation(Enemy::hit);
	m_enemy->SetSpeed(speed);
}
EnemyStateHit::~EnemyStateHit()
{

}
void EnemyStateHit::Update()
{
	m_enemy->SetSpeed(speed);
	speed /= 2.0f;
	if (!m_enemy->GetanimationPlaying()) {
		m_enemy->TransitionState(Enemy::State_Move);
	}
}
