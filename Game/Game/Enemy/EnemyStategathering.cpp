#include "stdafx.h"
#include "EnemyStategathering.h"
#include"Enemy.h"



EnemyStategathering::EnemyStategathering(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	path = enemy->CopyPath();
	path->Course(enemy->GetLeaderPosition(), enemy->Get3DPosition());
	m_nextpos = path->PathPos();
}

EnemyStategathering::~EnemyStategathering()
{
}
void EnemyStategathering::Update()
{
	CVector3 nowpos = enemy->Get3DPosition();
	nowpos.y = 0.0f;
	auto ka = enemy->GetLeaderPosition();
	ka.y = 0;
	CVector3 distance = ka - nowpos;
	if (distance.Length() <= 150.0f)
	{
		enemy->ChangeLeaderState(Enemyleader::gathering);
		enemy->SetSpeed(0.0f);
		enemy->Rollcall();
		return;
	}
	CVector3 speed = CVector3::Zero();
	speed = m_nextpos - nowpos;
	if (speed.Length() <= 50.0f)
	{
		m_nextpos = path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			enemy->ChangeLeaderState(Enemyleader::gathering);
			enemy->SetSpeed(0.0f);
			enemy->Rollcall();
			return;
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	enemy->FindAngle(speed);
	enemy->SetSpeed(500.0f);
}