#include "stdafx.h"
#include "EnemyStateTracking.h"
#include"../../Player/Player.h"
#include"Enemy.h"


EnemyStateTracking::EnemyStateTracking(Enemy* enemy,Player* player):EnemyState(enemy, player)
{
	m_vector = new VectorDraw(enemy->Get2DPosition());
}


EnemyStateTracking::~EnemyStateTracking()
{
	delete m_vector;
}
void EnemyStateTracking::Update()
{
	CVector3 speed = CVector3::Zero();
	auto distance = m_player->Get2Dposition() - m_enemy->Get2DPosition();
	speed = distance; 
	speed.y = 0.0f;
	speed.Normalize();
	m_enemy->FindAngle(speed);
	speed *= 300.0f;
	//enemy->Setmove(speed);
	CVector3 position = m_enemy->Get3DPosition();
	m_vector->Update(position, speed, 1.0);
	m_vector->Draw();
	if (distance.Length()>=500.0f)
	{
		//speed.y = 800.0f;
		//enemy->Setmove(speed);
		m_enemy->TransitionState(Enemy::State_Move);
	}
	if (distance.Length() >= 500.0f)
	{
		//speed.y = 800.0f;
		//enemy->Setmove(speed);
		m_enemy->TransitionState(Enemy::State_Move);
	}
}