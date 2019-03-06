#include "stdafx.h"
#include "EnemyStateHit.h"
#include"Enemy.h"

EnemyStateHit::EnemyStateHit(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	m_enemy->ChangeAnimation(Enemy::hit);
}
EnemyStateHit::~EnemyStateHit()
{

}
void EnemyStateHit::Update()
{
	if (!m_enemy->GetanimationPlaying()) {
		m_enemy->TransitionState(Enemy::State_Move);
	}
}