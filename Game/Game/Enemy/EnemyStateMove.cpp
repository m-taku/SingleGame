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
	if (speed.Length()<=250.0f)
	{
		m_nextpos = path.Pathpos();
	}
	speed.y = 0.0;
	speed.Normalize();
	speed *= 500.0f;
	enemy->Setspeed(speed);
	CVector3 distance = player->Get2Dposition() - enemy->Get2Dposition();	
	auto ka=(m_oldposition - nowpos).Length();
	auto ma = (m_nextpos - nowpos).Length();
	if ((m_oldposition - nowpos).Length()<=10.0f|| (m_nextpos- nowpos).Length()<=200.0f)
	{
		m_time++;
	}
	else
	{
		m_time = 0;
	}
	if (m_time >= 30)
	{
		path.course(enemy->Get2Dposition(), player->Get2Dposition());
		m_time = 0;
	}
	m_oldposition = enemy->Get3Dposition();
	if (distance.Length() <= 150.0f)
	{
		enemy->transitionState(Enemy::State_Tracking);
	}

}
