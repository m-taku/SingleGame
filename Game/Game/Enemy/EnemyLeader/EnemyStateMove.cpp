#include "stdafx.h"
#include "EnemyStateMove.h"
#include"Enemy.h"

EnemyStateMove::EnemyStateMove(Enemy* enamy,Player* player):EnemyState(enamy,player)
{
	path.course(enemy->Get2Dposition(), player->Get2Dposition());
	m_nextpos = path.Pathpos();
}
EnemyStateMove::~EnemyStateMove()
{
}
void EnemyStateMove::Update()
{
	CVector3 speed =CVector3::Zero();
	CVector3 nowpos = enemy->Get3Dposition();
	speed = m_nextpos - nowpos;
	if (speed.Length()<=100.0f)
	{
		m_nextpos = path.Pathpos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			path.course(enemy->Get2Dposition(), player->Get2Dposition());
			m_nextpos = path.Pathpos();
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	enemy->Findangle(speed);
	speed *= 500.0f;
	enemy->Setmove(speed);
	CVector3 distance = player->Get2Dposition() - enemy->Get2Dposition();	
	if (distance.Length() <= 150.0f)
	{
		enemy->transitionState(Enemy::State_Tracking);
	}
	else
	{
		if (distance.Length() >= 600.0f)
		{
			enemy->SetLeaderState(Enemyleader::gathering);
			enemy->SetLeaderposition(enemy->Get3Dposition());
		}
	}
}
