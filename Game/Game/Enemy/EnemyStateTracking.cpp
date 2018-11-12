#include "stdafx.h"
#include "EnemyStateTracking.h"
#include"../../Player/Player.h"
#include"Enemy.h"


EnemyStateTracking::EnemyStateTracking(Enemy* enemy,Player* player):EnemyState(enemy, player)
{
	vector = new VectorDraw(enemy->Get2DPosition());
}


EnemyStateTracking::~EnemyStateTracking()
{
	delete vector;
}
void EnemyStateTracking::Update()
{
	CVector3 speed = CVector3::Zero();
	auto distance = player->Get2Dposition() - enemy->Get2DPosition();
	speed = distance; 
	speed.y = 0.0f;
	speed.Normalize();
	enemy->FindAngle(speed);
	speed *= 300.0f;
	//enemy->Setmove(speed);
	CVector3 position = enemy->Get3DPosition();
	vector->Update(position, speed, 1.0);
	vector->Draw();
	if (distance.Length()>=500.0f)
	{
		//speed.y = 800.0f;
		//enemy->Setmove(speed);
		enemy->TransitionState(Enemy::State_Move);
	}
	if (distance.Length() >= 500.0f)
	{
		//speed.y = 800.0f;
		//enemy->Setmove(speed);
		enemy->TransitionState(Enemy::State_Move);
	}
}