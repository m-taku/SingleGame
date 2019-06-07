#include "stdafx.h"
#include "EnemyStateDead.h"
#include"Enemy.h"
#include"Gameover.h"


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
		if (m_enemy->GetStatus()->Spawnnum <= 1) 
		{
			if (nullptr == g_objectManager->FindGO<Gameover>("Gameover")) {
				g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover, "Gameover")->Setfra(false);
			}
		}
		m_enemy->DeleteEnemy();
		m_enemy->DeleteHitobj();
	}
}