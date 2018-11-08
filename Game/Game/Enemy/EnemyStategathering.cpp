#include "stdafx.h"
#include "EnemyStategathering.h"
#include"Enemy.h"



EnemyStategathering::EnemyStategathering(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
	path.course(enemy->GetLeaderposition(), enemy->Get3Dposition());
	m_nextpos = path.Pathpos();
}

EnemyStategathering::~EnemyStategathering()
{
}
void EnemyStategathering::Update()
{
	CVector3 nowpos = enemy->Get3Dposition();
	nowpos.y = 0.0f;
	auto ka = enemy->GetLeaderposition();
	ka.y = 0;
	CVector3 distance = ka - nowpos;
	if (distance.Length() <= 150.0f)
	{
		enemy->SetLeaderState(Enemyleader::gathering);
		enemy->Setmove(0.0f);
		enemy->Incrementninzuu();
		return;
	}
	CVector3 speed = CVector3::Zero();
	speed = m_nextpos - nowpos;
	if (speed.Length() <= 50.0f)
	{
		m_nextpos = path.Pathpos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			enemy->SetLeaderState(Enemyleader::gathering);
			enemy->Setmove(0.0f);
			enemy->Incrementninzuu();
			return;
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	enemy->Findangle(speed);
	enemy->Setmove(500.0f);
}