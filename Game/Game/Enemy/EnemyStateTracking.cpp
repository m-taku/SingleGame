#include "stdafx.h"
#include "EnemyStateTracking.h"
#include"../Player.h"
#include"Enemy.h"


EnemyStateTracking::EnemyStateTracking(Enemy* enemy,Player* player):EnemyState(enemy, player)
{

	kasa = new VectorDraw(enemy->Get2Dposition());
}


EnemyStateTracking::~EnemyStateTracking()
{
}
void EnemyStateTracking::Update()
{
	CVector3 speed = CVector3::Zero();
	auto distance = player->Get2Dposition() - enemy->Get2Dposition();
	speed = distance; 
	speed.Normalize();
	speed *= 300.0f;
	enemy->Setspeed(speed);
	CVector3 position = enemy->Get3Dposition();
//*	position.y = 10.0f;
	kasa->Update(position, speed, 1.0);
	kasa->Draw();
	if (distance.Length()>=500.0f)
	{
		speed.y = 800.0f;
		enemy->Setspeed(speed);
		enemy->transitionState(Enemy::State_Move);
	}

}