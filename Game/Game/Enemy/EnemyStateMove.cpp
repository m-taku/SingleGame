#include "stdafx.h"
#include "EnemyStateMove.h"
#include"Enemy.h"

EnemyStateMove::EnemyStateMove(Enemy* enamy,Player* player):EnemyState(enamy,player)
{

}
EnemyStateMove::~EnemyStateMove()
{
}
void EnemyStateMove::Update()
{
	CVector3 a=CVector3::Zero();
	//a.x = hanten  * 300.0f;
	//a.z = hanten  * 300.0f;
	enemy->Setspeed(a);
	//hanten *= -1;
	CVector3 distance = player->Get2Dposition() - enemy->Get2Dposition();
	if (distance.Length() <= 150.0f)
	{
		enemy->transitionState(Enemy::State_Tracking);
	}
}
