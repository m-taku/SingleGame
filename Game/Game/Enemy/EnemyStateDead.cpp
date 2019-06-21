#include "stdafx.h"
#include "EnemyStateDead.h"
#include"Enemy.h"
#include"Gameover.h"


EnemyStateDead::EnemyStateDead(Enemy* enamy, const CVector3* pos) :EnemyState(enamy, pos)
{
	m_enemy->ChangeAnimation(Enemy::idle);
	m_enemy->SetFrontSpeed(-10.0f);
}


EnemyStateDead::~EnemyStateDead()
{
}
void EnemyStateDead::Update()
{
	
	if (m_enemy->ColliderOnGround())
	{
		m_enemy->SetFrontSpeed(0.0f);
	}
	else {
		m_enemy->SetFrontSpeed(-5.0f);
	}
	//if (!m_enemy->GetanimationPlaying()) 
	//{

	//}
	if (kakudo < 90) {
		CQuaternion k;
		auto ma = m_enemy->Get2DRight();
		k.SetRotationDeg(ma, -6.0f);
		m_enemy->AddAngle(k);
		kakudo += 6.0f;
	}
	else
	{
		if (m_enemy->GetStatus()->m_Spawnnum <= 1)
		{

			if (nullptr == g_objectManager->FindGO<Gameover>("Gameover")) {
				g_objectManager->NewGO<Gameover>(GameObjectPriority_Gameover, "Gameover")->Setfra(false);
			}
		}
		m_enemy->DeleteEnemy();
		m_enemy->DeleteHitobj();

	}
}