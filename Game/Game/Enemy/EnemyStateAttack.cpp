#include "stdafx.h"
#include "EnemyStateAttack.h"
#include"../../Player/Player.h"
#include"Enemy.h"

EnemyStateAttack::EnemyStateAttack(Enemy* enamy, Player* player) :EnemyState(enamy, player)
{
}


EnemyStateAttack::~EnemyStateAttack()
{
}
void EnemyStateAttack::Update()
{
	player->Ui->SetDamage(0.001f);
	auto distance = player->Get2Dposition() - enemy->Get2DPosition();
	if (distance.Length() >= 200.0f)
	{
		//speed.y = 800.0f;
		enemy->TransitionState(Enemy::State_Tracking);
	}
}