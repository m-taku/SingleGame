#include "stdafx.h"
#include "EnemyStateMove.h"
#include"Enemy.h"

EnemyStateMove::EnemyStateMove(Enemy* enamy,Player* player):EnemyState(enamy,player)
{
	m_path = m_enemy->CopyPath();
	m_path->Course(m_enemy->Get2DPosition(), player->Get2Dposition());
	m_nextpos = m_path->PathPos();
}
EnemyStateMove::~EnemyStateMove()
{

}
void EnemyStateMove::Update()
{
	//path.course(enemy->Get2Dposition(), player->Get2Dposition());
	//m_nextpos = path.Pathpos();
	CVector3 speed =CVector3::Zero();
	CVector3 nowpos = m_enemy->Get3DPosition();
	speed = m_nextpos - nowpos;
	if (speed.Length()<=50.0f)
	{
		m_nextpos = m_path->PathPos();
		if (m_nextpos.x == m_oldposition.x&&m_nextpos.y == m_oldposition.y&&m_nextpos.z == m_oldposition.z)
		{
			m_path->Course(m_enemy->Get2DPosition(), m_player->Get2Dposition());
			m_nextpos = m_path->PathPos();
		}
		m_oldposition = m_nextpos;
	}
	speed.y = 0.0;
	speed.Normalize();
	m_enemy->FindAngle(speed);
	//speed *= 500.0f;
	m_enemy->SetSpeed(500.0f);
	CVector3 distance = m_player->Get2Dposition() - m_enemy->Get2DPosition();	
	//if (distance.Length() <= 150.0f)
	//{
	//	enemy->transitionState(Enemy::State_Tracking);
	//}
	//else
	{
		if (distance.Length() >= 600.0f)
		{
			m_enemy->ChangeLeaderState(Enemyleader::gathering);
			m_enemy->SetLeaderPosition(m_enemy->Get3DPosition());
		}
	}
}
