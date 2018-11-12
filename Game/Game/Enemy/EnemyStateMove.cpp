#include "stdafx.h"
#include "EnemyStateMove.h"
#include"Enemy.h"

EnemyStateMove::EnemyStateMove(Enemy* enamy,Player* player):EnemyState(enamy,player)
{
	path = enemy->CopyPath();
	path->Course(enemy->Get2DPosition(), player->Get2Dposition());
	m_nextpos = path->PathPos();
}
EnemyStateMove::~EnemyStateMove()
{

}
void EnemyStateMove::Update()
{
	//path.course(enemy->Get2Dposition(), player->Get2Dposition());
	//m_nextpos = path.Pathpos();
	CVector3 speed =CVector3::Zero();
	CVector3 nowpos = enemy->Get3DPosition();
	speed = m_nextpos - nowpos;
	if (speed.Length()<=50.0f)
	{
		m_nextpos = path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			path->Course(enemy->Get2DPosition(), player->Get2Dposition());
			m_nextpos = path->PathPos();
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	enemy->FindAngle(speed);
	//speed *= 500.0f;
	enemy->SetSpeed(500.0f);
	CVector3 distance = player->Get2Dposition() - enemy->Get2DPosition();	
	//if (distance.Length() <= 150.0f)
	//{
	//	enemy->transitionState(Enemy::State_Tracking);
	//}
	//else
	{
		if (distance.Length() >= 600.0f)
		{
			enemy->ChangeLeaderState(Enemyleader::gathering);
			enemy->SetLeaderposition(enemy->Get3DPosition());
		}
	}
}
