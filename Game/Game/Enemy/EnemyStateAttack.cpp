#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"../../Player/Player.h"
#include"Enemy.h"


EnemyStateAttack::EnemyStateAttack(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
}


EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{
	m_player->Damage(0.001f);
	auto distance = m_player->Get2Dposition() - m_enemy->Get2DPosition();
	if (distance.Length() >= 200.0f)
	{
		//speed.y = 800.0f;
		m_enemy->TransitionState(Enemy::State_Tracking);
	}
}