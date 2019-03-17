#include "stdafx.h"
#include "EnemyStateDead.h"
#include"Enemy.h"


EnemyStateDead::EnemyStateDead(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	m_enemy->ChangeAnimation(Enemy::dead);
	m_enemy->SetSpeed(0.0f);
}


EnemyStateDead::~EnemyStateDead()
{
}
void EnemyStateDead::Update()
{
	if (!m_enemy->GetanimationPlaying()) 
	{
		m_enemy->DeleteEnemy();
		m_enemy->DeleteHitobj();
	}
}